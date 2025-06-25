/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstwrapper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intherna <intherna@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:19:35 by intherna          #+#    #+#             */
/*   Updated: 2025/06/19 17:24:46 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lst_init(t_list_w *list)
{
	list->first = NULL;
	list->last = NULL;
	list->size = 0;
}

t_list	*lst_add(t_list_w *list, void *item)
{
	t_list	*node;

	node = ft_lstnew(item);
	if (node == NULL)
		return (NULL);
	list->size++;
	if (list->first == NULL)
		list->first = node;
	if (list->last == NULL)
	{
		list->last = node;
		return (node);
	}
	list->last->next = node;
	list->last = node;
	return (node);
}

void	*lst_clear(t_list_w *list, void (*del)(void *))
{
	ft_lstclear(&list->first, del);
	list->size = 0;
	list->first = NULL;
	list->last = NULL;
	return (NULL);
}

t_list	*lst_addfirst(t_list_w *list, void *item)
{
	t_list	*node;

	node = ft_lstnew(item);
	if (node == NULL)
		return (NULL);
	node->next = list->first;
	list->first = node;
	if (node->next == NULL)
		list->last = node;
	list->size++;
	return (node);
}

t_list	*lst_addbefore(t_list_w *list, void *item, t_list *before)
{
	t_list	*actual;
	t_list	*previous;
	t_list	*res;

	actual = list->first;
	previous = NULL;
	while (actual != NULL && actual != before)
	{
		previous = actual;
		actual = actual->next;
	}
	if (actual == NULL)
		return (NULL);
	if (list->size == 0 || previous == NULL)
		return (lst_addfirst(list, item));
	res = ft_lstnew(item);
	if (res == NULL)
		return (NULL);
	previous->next = res;
	res->next = actual;
	list->size++;
	return (res);
}
