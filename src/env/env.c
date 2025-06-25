/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:17:22 by cmarrued          #+#    #+#             */
/*   Updated: 2025/06/22 16:00:44 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	**copy_env(char **envp)
{
	int		i;
	char	**copy;

	if (!envp)
		return (NULL);
	i = -1;
	while (envp[++i])
		;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = -1;
	while (envp[++i])
		copy[i] = ft_strdup(envp[i]);
	copy[i] = NULL;
	return (copy);
}

/**
* Returns new entry of value and key for env.
*/
char	*gen_pair(char *key, char *value)
{
	int		len_entry;
	int		len_value;
	char	*res;

	len_entry = ft_strlen(key);
	len_value = ft_strlen(value);
	res = malloc(len_entry + len_value + 2);
	if (!res)
		return (NULL);
	ft_memcpy(res, key, len_entry);
	res[len_entry] = '=';
	ft_memcpy(res + len_entry + 1, value, len_value + 1);
	return (res);
}

/**
* Returns the length of env if doesn't exist.
*/
static int	replace_if_exists(char **env, const char *entry, char *newvalue)
{
	int		len_entry;
	char	*tmp;
	int		i;

	if (*entry == '$')
		entry++;
	i = 0;
	len_entry = ft_strlen(entry);
	while (env[i])
	{
		if (ft_strncmp((char *)entry, env[i],
				len_entry) == 0 && env[i][len_entry] == '=')
		{
			tmp = gen_pair((char *)entry, newvalue);
			if (!tmp)
				return (-1);
			free(env[i]);
			env[i] = tmp;
			return (1);
		}
		i++;
	}
	return (0);
}

int	set_env_value(char ***env, const char *entry, char *value)
{
	char	**res;
	int		replaced;
	int		i;

	replaced = replace_if_exists(*env, entry, value);
	if (replaced == -1)
		return (0);
	else if (replaced == 1)
		return (1);
	res = malloc(sizeof(char *) * (envlen(*env) + 2));
	if (!res)
		return (0);
	i = 0;
	while ((*env)[i])
	{
		res[i] = (*env)[i];
		i++;
	}
	free(*env);
	res[i] = gen_pair((char *)entry, value);
	if (!res[i])
		return (0);
	res[i + 1] = NULL;
	*env = res;
	return (1);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}
