/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:10:26 by cmarrued          #+#    #+#             */
/*   Updated: 2025/06/30 17:52:44 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "exit", 5));
}

int	exec_builtin(t_cmd *cmd, char ***env, t_state *state, uint_fast8_t is_main)
{
	int	ret;

	ret = 1;
	if (!ft_strncmp(cmd->args[0], "cd", 3))
		ret = ft_cd(cmd->args, cmd->argc, env, state);
	else if (!ft_strncmp(cmd->args[0], "export", 7))
		ret = ft_export(cmd->args, env, state);
	else if (!ft_strncmp(cmd->args[0], "unset", 6))
		ret = ft_unset(cmd->args, env, state);
	else if (!ft_strncmp(cmd->args[0], "exit", 5))
		ft_exit(cmd, state, is_main);
	else if (!ft_strncmp(cmd->args[0], "pwd", 4))
		ret = ft_pwd(cmd->settings.pseudo_stdout, state);
	else if (!ft_strncmp(cmd->args[0], "env", 4))
		ret = ft_env(*env, cmd->settings.pseudo_stdout);
	else if (!ft_strncmp(cmd->args[0], "echo", 5))
		ret = ft_echo(cmd->args, cmd->settings.pseudo_stdout);
	if (!is_main)
	{
		free_env(*env);
		clean_cmd(cmd);
		rl_clear_history();
	}
	return (ret);
}
