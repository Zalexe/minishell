/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:26:34 by cmarrued          #+#    #+#             */
/*   Updated: 2025/06/26 18:33:11 by intherna         ###   ########.fr       */
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

int	run_child(t_cmd *cmd, char **env, int is_last)
{
	t_pipe_args	args;
	int			res;

	args = (t_pipe_args){cmd, {0, {NULL, 0},
		env, NULL, 0, ""}, -1, -1, is_last};
	if (cmd->settings.pseudo_stdin != -1)
		args.input_fd = cmd->settings.pseudo_stdin;
	if (cmd->settings.pseudo_stdout != -1 || !is_last)
		args.pipe_write_fd = cmd->settings.pseudo_stdout;
	res = child_process(&args);
	return (res);
}

static int	run_pipe(t_cmd *cmd, t_state *state, int input_fd, int is_last)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (!is_last && pipe(pipe_fd) < 0)
		return (perror("pipe"), 1);
	if (cmd->settings.pseudo_stdin == -1)
		cmd->settings.pseudo_stdin = input_fd;
	if (!is_last && cmd->settings.pseudo_stdout == -1)
		cmd->settings.pseudo_stdout = pipe_fd[1];
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (!is_last)
			close(pipe_fd[0]);
		exit(run_child(cmd, state->env, is_last));
	}
	if (input_fd != 0)
		close(input_fd);
	if (!is_last)
		return (close(pipe_fd[1]), pipe_fd[0]);
	return (parent_process(pid));
}

int	handle_pipe(t_cmd **cmds, int amount, t_state *state)
{
	int		i;
	int		input_fd;
	int		last;
	int		res;

	i = -1;
	input_fd = 0;
	while (++i < amount)
	{
		last = ((i + 1) == amount);
		res = run_pipe(cmds[i], state, input_fd, last);
		if (res == -1)
			break ;
		if (last)
			state->status = res;
		else
			input_fd = res;
	}
	return (state->status);
}
