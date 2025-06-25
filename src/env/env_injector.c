/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_injector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intherna <intherna@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:18:06 by intherna          #+#    #+#             */
/*   Updated: 2025/06/19 16:37:47 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "type_utils.h"
#include "minishell.h"

static int	get_len(char *var)
{
	int	len;

	len = 0;
	if (*var == '$')
		len++;
	if (var[len] == '?' || ft_isdigit(var[len]))
		return (len + 1);
	while (ft_isalnum(var[len]))
		len++;
	return (len);
}

char	*ft_strjoin3(t_slice s1, t_slice s2, t_slice s3)
{
	char	*res;
	size_t	i;
	size_t	j;

	res = malloc(s1.len + s2.len + s3.len + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (j < s1.len)
		res[i++] = s1.str[j++];
	j = 0;
	while (j < s2.len)
		res[i++] = s2.str[j++];
	j = 0;
	while (j < s3.len)
		res[i++] = s3.str[j++];
	res[i] = '\0';
	return (res);
}

t_str	get_env(char *str, char **env, uint8_t status)
{
	int	len;

	if (*str == '$')
		str++;
	if (*str == '?')
		return ((t_str){ft_itoa(status), 1});
	len = get_len(str);
	if (len == 0)
		return ((t_str){"$", 0});
	while (*env)
	{
		if (ft_strncmp(str, *env, len) == 0 && (*env)[len] == '=')
			return ((t_str){(*env) + len + 1, 0});
		env++;
	}
	return ((t_str){"", 0});
}

/**
* Replace all $ env vars with corresponding values. Returns a malloc pointer
*/
char	*inject_env(char *dst, char **env, uint8_t status,
			char *(*delchr)(char *))
{
	t_env_vars	v;

	v = (t_env_vars){ft_strdup(dst), NULL, NULL, {NULL, 0}, 0, 0};
	while (v.res)
	{
		v.find = delchr(v.res + v.i_tmp);
		if (!v.find)
			break ;
		v.i_tmp = get_len(v.find);
		v.rep = get_env(v.find, env, status);
		if (!v.rep.str)
			return (free(v.res), NULL);
		v.i_tmp2 = ft_strlen(v.rep.str);
		v.tmp = ft_strjoin3((t_slice){v.res, v.find - v.res},
				(t_slice){v.rep.str, v.i_tmp2},
				(t_slice){v.find + v.i_tmp, ft_strlen(v.find) - v.i_tmp});
		v.i_tmp = v.i_tmp2 + (v.find - v.res);
		if (v.rep.is_malloc)
			free(v.rep.str);
		free(v.res);
		if (!v.tmp)
			return (NULL);
		v.res = v.tmp;
	}
	return (v.res);
}
