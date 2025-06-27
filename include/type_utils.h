/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intherna <intherna@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:50:29 by intherna          #+#    #+#             */
/*   Updated: 2025/06/27 20:08:05 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_UTILS_H
# define TYPE_UTILS_H

# include "minishell.h"
# include <dirent.h>

typedef struct s_env_vars
{
	char		*res;
	t_chr_res	find;
	char		*tmp;
	t_str		rep;
	int			i_tmp;
	int			i_tmp2;
}	t_env_vars;

typedef struct s_astsk_vars
{
	char		*res;
	char		*find;
	t_list_w	files;
	DIR			*dir;
	char		*tmp;
	char		*tmp2;
	char		*tmp3;
	size_t		nv_len;
	size_t		i_tmp;
}	t_astsk_vars;

typedef struct s_export_vars
{
	int		i;
	char	*key;
	char	*value;
	char	*tmp;
}	t_export_vars;

typedef struct s_parse_vars
{
	t_slice			arg;
	int				pos;
	t_parse_result	res;
}	t_parse_vars;

#endif
