/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_injector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intherna <intherna@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:18:06 by intherna          #+#    #+#             */
/*   Updated: 2025/06/27 20:28:44 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "type_utils.h"
#include "minishell.h"

#define EMPTY ""

static int	get_len(char *var, uint_fast8_t quote)
{
	int	len;

	len = 0;
	if (var[len] == '$')
		len++;
	if ((var[len] == '\'' || var[len] == '"') && !quote)
		return (1);
	if (var[len] == '?' || ft_isdigit(var[len]) || var[len] == '$')
		return (len + 1);
	while (ft_isalnum(var[len]) || var[len] == '_')
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
	if (*str == '\'' || *str == '"')
		return ((t_str){EMPTY, 0});
	if (*str == '?')
		return ((t_str){ft_itoa(status), 1});
	len = get_len(str, 0);
	if (len == 0)
		return ((t_str){"$", 0});
	while (*env)
	{
		if (ft_strncmp(str, *env, len) == 0 && (*env)[len] == '=')
			return ((t_str){(*env) + len + 1, 0});
		env++;
	}
	return ((t_str){EMPTY, 0});
}

static t_str	get_env_int(char *str, char **env,
					t_state *s, uint_fast8_t quote)
{
	int	len;

	if (*str == '$')
		str++;
	if ((*str == '\'' || *str == '"') && !quote)
		return ((t_str){EMPTY, 0});
	if (*str == '$')
		return ((t_str){s->pid, 0});
	if (*str == '?')
		return ((t_str){ft_itoa(s->status), 1});
	len = get_len(str, quote);
	if (len == 0)
		return ((t_str){"$", 0});
	while (*env)
	{
		if (ft_strncmp(str, *env, len) == 0 && (*env)[len] == '=')
			return ((t_str){(*env) + len + 1, 0});
		env++;
	}
	return ((t_str){EMPTY, 0});
}

/**
* Replace all $ env vars with corresponding values. Returns a malloc pointer
*/
char	*inject_env(char *dst, char **env, t_state *state,
			t_chr_res (*delchr)(char *))
{
	t_env_vars	v;

	v = (t_env_vars){ft_strdup(dst), {NULL, 0}, NULL, {NULL, 0}, 0, 0};
	while (v.res)
	{
		v.find = delchr(v.res + v.i_tmp);
		if (!v.find.s)
			break ;
		v.i_tmp = get_len(v.find.s, v.find.quote);
		v.rep = get_env_int(v.find.s, env, state, v.find.quote);
		if (!v.rep.str)
			return (free(v.res), NULL);
		v.i_tmp2 = ft_strlen(v.rep.str);
		v.tmp = ft_strjoin3((t_slice){v.res, v.find.s - v.res},
				(t_slice){v.rep.str, v.i_tmp2},
				(t_slice){v.find.s + v.i_tmp, ft_strlen(v.find.s) - v.i_tmp});
		v.i_tmp = v.i_tmp2 + (v.find.s - v.res);
		if (v.rep.is_malloc)
			free(v.rep.str);
		free(v.res);
		if (!v.tmp)
			return (NULL);
		v.res = v.tmp;
	}
	return (v.res);
}
