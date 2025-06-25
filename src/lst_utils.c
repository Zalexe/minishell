/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intherna <intherna@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:40:42 by intherna          #+#    #+#             */
/*   Updated: 2025/06/23 21:53:03 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/**
* Filter a list given a criteria (criteria function)
*
* params:
*
* list: list to filter
* str: string to be compared against
* crit: function that returns true (0<) if the item passes the criteria
* with the string provided, or 0 if it does not.
* d: delete function, to remove items that don't pass the criteria
*/
void	filter_match(t_list_w *list, char *str,
		int (*crit)(char *, char *), void (*d)(void *))
{
	t_list	*node;
	t_list	*last;
	t_list	*tmp;

	node = list->first;
	last = NULL;
	while (node)
	{
		if (!crit(node->content, str))
		{
			list->size--;
			if (last)
				last->next = node->next;
			else
				list->first = node->next;
			if (list->size == 0)
				list->last = NULL;
			tmp = node;
			node = tmp->next;
			ft_lstdelone(tmp, d);
			continue ;
		}
		last = node;
		node = node->next;
	}
}

static t_slice	rec_join(t_list *node, char del, t_slice sl)
{
	size_t	size;
	size_t	pos;
	t_slice	res;

	if (!node)
	{
		sl.str = malloc(sl.len);
		return (sl);
	}
	size = ft_strlen(node->content);
	pos = sl.len;
	res = rec_join(node->next, del, (t_slice){sl.str, pos + size + 1});
	if (!res.str)
		return (res);
	ft_memcpy(res.str + pos, node->content, size);
	res.str[pos + size] = del;
	return (res);
}

/**
* Concatenate all items in the list in a single string, separated by del
*
* params:
*
* list: the list to concatenate
* del: the character that acts as a delimiter between items
*/
char	*join(t_list_w *list, char del)
{
	t_slice	res;

	if (list->size == 0)
		return (NULL);
	res = rec_join(list->first, del, (t_slice){NULL, 0});
	if (!res.str)
		return (NULL);
	res.str[res.len - 1] = '\0';
	return (res.str);
}

int	is_in_list(t_list *list, const char *key)
{
	while (list)
	{
		if (ft_strncmp((char *)list->content, key, ft_strlen(key)) == 0)
			return (1);
		list = list->next;
	}
	return (0);
}
