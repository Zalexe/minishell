/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:27:44 by cmarrued          #+#    #+#             */
/*   Updated: 2025/06/16 22:43:40 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * cmd: cmd singular que ejecutar
 * env: nuestro env propio ya generado
 * execute para pipes, sin usar fork
 */
int	execute_command_no_fork(t_cmd *cmd, char **env)
{
	char	*path;

	path = get_command_path(cmd->args[0], env);
	if (!path)
	{
		perror("command not found");
		exit(127);
	}
	if (execve(path, cmd->args, env) == -1)
	{
		free(path);
		if (errno == ENOENT)
		{
			perror("No such file or directory");
			exit(127);
		}
		else if (errno == EACCES)
		{
			perror("Permission denied");
			exit(126);
		}
		else
			exit(1);
	}
	return (0);
}
