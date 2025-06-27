/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:26:34 by cmarrued          #+#    #+#             */
/*   Updated: 2025/06/27 20:52:17 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	child_process(t_pipe_args *args)
{
	if (args->cmd->settings.failed)
		exit(1);
	if (args->input_fd != -1
		&& args->input_fd != STDIN_FILENO)
	{
		dup2(args->input_fd, STDIN_FILENO);
		close(args->input_fd);
	}
	if (args->pipe_write_fd != -1
		&& args->pipe_write_fd != STDOUT_FILENO)
	{
		dup2(args->pipe_write_fd, STDOUT_FILENO);
		close(args->pipe_write_fd);
		args->cmd->settings.pseudo_stdout = STDOUT_FILENO;
	}
	if (!args->cmd->args || !args->cmd->args[0])
		exit(0);
	args->cmd->settings.pseudo_stdout = STDOUT_FILENO;
	if (is_builtin(args->cmd->args[0]))
		exit(exec_builtin(args->cmd, &args->state.env, &args->state, 0));
	return (execute_command_no_fork(args->cmd, args->state.env));
}

static int	parent_process(pid_t pid)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid error");
		return (1);
	}
	init_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(2, "\n", 1);
		return (128 + WTERMSIG(status));
	}
	else
		return (status);
}

int	run_child(t_cmd *cmd, char **env)
{
	t_pipe_args	args;
	int			res;

	args = (t_pipe_args){cmd, {0, {NULL, 0},
		env, NULL, 0, "", ""}, -1, -1, 0};
	if (cmd->settings.pseudo_stdin != -1)
		args.input_fd = cmd->settings.pseudo_stdin;
	if (cmd->settings.pseudo_stdout != -1)
		args.pipe_write_fd = cmd->settings.pseudo_stdout;
	res = child_process(&args);
	return (res);
}

static pid_t	run_pipe(t_cmd *cmd, t_state *state, int pipe_fd[2],
				int input_fd)
{
	pid_t	pid;

	if (cmd->settings.pseudo_stdin == -1)
		cmd->settings.pseudo_stdin = input_fd;
	if (cmd->settings.pseudo_stdout == -1)
		cmd->settings.pseudo_stdout = pipe_fd[1];
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		exit(run_child(cmd, state->env));
	}
	return (pid);
}

int	handle_pipe(t_cmd **cmds, int i, int amount[2], t_state *state)
{
	int		pipe_fd[2];
	int		status_last;
	pid_t	res;

	if (pipe(pipe_fd) < 0)
		return (perror("pipe"), 1);
	if (i == amount[0] - 1)
	{
		res = run_pipe(cmds[i], state,
				(int [2]){pipe_fd[0], STDOUT_FILENO}, amount[1]);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		close(amount[1]);
		return (parent_process(res));
	}
	else
		res = run_pipe(cmds[i], state, pipe_fd, amount[1]);
	close(pipe_fd[1]);
	status_last = handle_pipe(cmds, i + 1,
			(int [2]){amount[0], pipe_fd[0]}, state);
	close(pipe_fd[0]);
	if (i != 0)
		close(amount[1]);
	parent_process(res);
	return (status_last);
}
