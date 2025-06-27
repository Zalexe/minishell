/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:26:29 by cmarrued          #+#    #+#             */
/*   Updated: 2025/06/27 20:11:07 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static t_chr_res	dollar_del_chr(char *str)
{
	while (*str)
	{
		if (*str == '$')
			return ((t_chr_res){str, 0});
		str++;
	}
	return ((t_chr_res){NULL, 0});
}

static char	*inject(char **line, char **env, t_state *state)
{
	char	*tmp;

	tmp = inject_env(*line, env, state, &dollar_del_chr);
	free(*line);
	*line = tmp;
	return (*line);
}

static void	heredoc_child(int write_fd, char *eof,
				uint_fast8_t env, t_state *state)
{
	char	*line;

	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, eof, ft_strlen(line)) == 0)
		{
			if (!line)
				print_error("warning: EOF reached", 0, 0, state);
			clean_return(line);
			break ;
		}
		if (env && !inject(&line, state->env, state))
		{
			close(write_fd);
			exit(1);
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
	exit(0);
}

static int	heredoc_parent(int fd[2], pid_t pid,
				t_cmd_settings *settings, t_state *state)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	close(fd[1]);
	waitpid(pid, &status, 0);
	init_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		close(fd[0]);
		state->status = 130;
		return (130);
	}
	if (WEXITSTATUS(status) != 0)
	{
		close(fd[0]);
		state->status = WEXITSTATUS(status);
		return (0);
	}
	settings->pseudo_stdin = fd[0];
	return (1);
}

int	handle_heredoc(t_cmd_settings *settings, char *eof,
			uint_fast8_t env, t_state *state)
{
	int		fds[2];
	pid_t	pid;

	if (pipe(fds) == -1)
		return (print_error(NULL, errno, 1, state), 0);
	pid = fork();
	if (pid < 0)
	{
		close(fds[0]);
		close(fds[1]);
		return (print_error("fork", errno, 1, state), 0);
	}
	if (pid == 0)
	{
		close(fds[0]);
		heredoc_child(fds[1], eof, env, state);
	}
	return (heredoc_parent(fds, pid, settings, state));
}
