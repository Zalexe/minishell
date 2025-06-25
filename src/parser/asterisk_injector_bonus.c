/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk_injector_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intherna <intherna@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:21:45 by intherna          #+#    #+#             */
/*   Updated: 2025/06/23 21:57:52 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "type_utils.h"
#include <dirent.h>
#include <unistd.h>

static void	dummy(void *i)
{
	if (i)
		return ;
}

static int	populate_files(t_list_w *list, t_state *state, t_astsk_vars *v)
{
	struct dirent	*ent;
	char			*end;

	end = argdelimitchr(v->find);
	end = rev_quotes(end, end - v->find);
	while (is_consecutive_quote(v->find))
		v->find += 2;
	v->dir = opendir(".");
	if (!v->dir)
		return (print_error(NULL, errno, 1, state), 0);
	ent = readdir(v->dir);
	while (ent)
	{
		if (ft_strncmp(v->find, "*", end - v->find) == 0
			&& ent->d_name[0] == '.')
		{
			ent = readdir(v->dir);
			continue ;
		}
		lst_add(list, ent->d_name);
		ent = readdir(v->dir);
	}
	return (1);
}

static int	aux_inject_astsk(t_astsk_vars *v, t_state *state)
{
	while (v->find)
	{
		if (!populate_files(&v->files, state, v))
			return (0);
		filter_match(&v->files, v->find, &astsk_criteria, &dummy);
		v->tmp = join(&v->files, ' ');
		if (!v->tmp)
			return (closedir(v->dir), 0);
		v->nv_len = ft_strlen(v->tmp);
		v->i_tmp = v->find - v->res;
		v->tmp3 = argdelimitchr(v->find);
		v->tmp2 = ft_strjoin3((t_slice){v->res, v->find - v->res},
				(t_slice){v->tmp, v->nv_len},
				(t_slice){v->tmp3, ft_strlen(v->tmp3)});
		if (!v->tmp2)
			return (free(v->tmp), closedir(v->dir),
				print_error_no_state(NULL, errno), 0);
		free(v->tmp);
		free(v->res);
		v->res = v->tmp2;
		v->find = astsk_chr(skip_whitespaces(v->tmp2 + v->i_tmp + v->nv_len));
		lst_clear(&v->files, &dummy);
		closedir(v->dir);
	}
	return (1);
}

/**
* Replace all * with corresponding files. Returns a malloc pointer
*/
char	*inject_astsk(char *dst, t_state *state)
{
	t_astsk_vars	v;

	v = (t_astsk_vars){ft_strdup(dst),
		NULL, {NULL, NULL, 0}, NULL, NULL, NULL, NULL, 0, 0};
	free(dst);
	if (!v.res)
		return (print_error(NULL, errno, 1, state), NULL);
	v.find = astsk_chr(v.res);
	aux_inject_astsk(&v, state);
	return (v.res);
}
