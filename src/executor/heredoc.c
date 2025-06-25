/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:26:29 by cmarrued          #+#    #+#             */
/*   Updated: 2025/06/22 18:03:23 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static char	*dollar_del_chr(char *str)
{
	while (*str)
	{
		if (*str == '$')
			return (str);
		str++;
	}
	return (NULL);
}

static char	*inject(char **line, char **env, uint8_t status)
{
	char	*tmp;

	tmp = inject_env(*line, env, status, &dollar_del_chr);
	free(*line);
	*line = tmp;
	return (*line);
}

int	handle_heredoc(t_cmd_settings *settings, char *eof,
			uint_fast8_t env, t_state *state)
{
	int		fds[2];
	char	*line;

	if (pipe(fds) == -1)
		return (print_error(NULL, errno, 1, state), 0);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, eof, ft_strlen(line)) == 0)
		{
			clean_return(line);
			if (!line)
				print_error("warning: EOF reached", 0, 0, state);
			break ;
		}
		if (env)
			if (!inject(&line, state->env, state->status))
				return (close(fds[0]), close(fds[1]), 0);
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		free(line);
	}
	settings->pseudo_stdin = fds[0];
	return (close(fds[1]), 1);
}
