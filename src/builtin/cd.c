/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:10:33 by cmarrued          #+#    #+#             */
/*   Updated: 2025/06/27 20:54:27 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_old_pwd(char ***env, t_state *state)
{
	if (!getcwd(state->pwd, PATH_MAX) || !set_env_value(env,
			"OLDPWD", get_env("PWD", *env, state->status).str)
		|| !set_env_value(env, "PWD", state->pwd))
		return (1);
	return (0);
}

int	ft_cd(char **args, char ***env, t_state *state)
{
	t_str	path;

	if (args[2])
		return (print_error("too many arguments", 0, 1, state), 1);
	if (!args[1] || !ft_strncmp(args[1], "--", 3))
		path = get_env("HOME", *env, state->status);
	else if (!ft_strncmp(args[1], "-", 2))
	{
		path = get_env("OLDPWD", *env, state->status);
		if (!path.str)
			return (print_error("OLDPWD not set", 0, 1, state), 1);
		ft_printf("%s\n", path.str);
	}
	else
		path = (t_str){args[1], 0};
	if (chdir(path.str) != 0)
		return (print_error(NULL, errno, 1, state), 1);
	return (set_old_pwd(env, state));
}
