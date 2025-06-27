/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intherna <intherna@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:43:08 by intherna          #+#    #+#             */
/*   Updated: 2025/06/27 20:13:18 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envlen(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

t_chr_res	envchr(char *str)
{
	uint_fast8_t	quote[2];
	uint_fast8_t	heredoc;

	quote[0] = 0;
	quote[1] = 0;
	heredoc = 0;
	while (*str)
	{
		if (*str == '<' && *(str + 1) == '<' && !quote[0] && !quote[1])
		{
			heredoc = 1;
			str = skip_whitespaces(str + 2);
			continue ;
		}
		if (*str == '$' && !quote[0] && !heredoc)
			return ((t_chr_res){str, quote[1]});
		if (*str == '\'' && !quote[1])
			quote[0] = !quote[0];
		if (*str == '"' && !quote[0])
			quote[1] = !quote[1];
		str++;
		if (heredoc && is_arg_delimiter(*str))
			heredoc = 0;
	}
	return ((t_chr_res){NULL, 0});
}

char	*get_key(const char *env_entry)
{
	int		len;

	len = 0;
	while (env_entry[len] && env_entry[len] != '=')
		len++;
	return (ft_substr(env_entry, 0, len));
}

char	*get_value(const char *env_entry)
{
	const char	*eq = ft_strchr(env_entry, '=');

	if (!eq)
		return (NULL);
	return ((char *)(eq + 1));
}

int	is_in_env(char **env, const char *key)
{
	int		i;
	int		len;

	if (!key || !env)
		return (0);
	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
			return (1);
		i++;
	}
	return (0);
}
