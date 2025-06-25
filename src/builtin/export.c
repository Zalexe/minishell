/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:10:59 by cmarrued          #+#    #+#             */
/*   Updated: 2025/06/14 20:11:43 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "type_utils.h"
#include "libft.h"

static int	is_valid_key(const char *str)
{
	int	i;

	i = 0;
	if (!str || !ft_isalpha(str[0]))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	no_args(char **env, t_list *export_list)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (env[i])
	{
		key = get_key(env[i]);
		value = get_value(env[i]);
		if (key && key[0])
			ft_printf("declare -x %s=\"%s\"\n", key, value);
		free(key);
		i++;
	}
	while (export_list)
	{
		ft_printf("declare -x %s\n", (char *)export_list->content);
		export_list = export_list->next;
	}
}

static int	export_loop(char **args, t_export_vars v,
				char ***env, t_state *state)
{
	while (args[v.i])
	{
		v.key = args[v.i];
		v.tmp = ft_strchr(args[v.i], '=');
		if (!is_valid_key(v.key))
			return (print_error("not a valid identifier", 0, 1, state), 1);
		v.i++;
		if (!v.tmp)
		{
			if (!is_in_env(*env, v.key)
				&& !is_in_list(state->export_list, v.key))
				ft_lstadd_back(&state->export_list,
					ft_lstnew(ft_strdup(v.key)));
			continue ;
		}
		*v.tmp = '\0';
		v.value = v.tmp + 1;
		if (!set_env_value(env, v.key, v.value))
			return (print_error(NULL, errno, 1, state), errno);
		remove_from_export_list(&state->export_list, v.key);
	}
	return (0);
}

int	ft_export(char **args, char ***env, t_state *state)
{
	t_export_vars	v;
	int				res;

	v = (t_export_vars){1, NULL, NULL, NULL};
	res = 0;
	if (!args[v.i])
		return (no_args(*env, state->export_list), 0);
	res = export_loop(args, v, env, state);
	return (res);
}
