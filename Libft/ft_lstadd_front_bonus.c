/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:52:19 by cmarrued          #+#    #+#             */
/*   Updated: 2024/12/23 17:52:21 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
/*
#include <stdio.h>
static void print_list(t_list *lst) {
	t_list *temp = lst;
	while (temp != NULL) {
		printf("%p -> ", temp->content);
		temp = temp->next;
	}
	printf("NULL\n");
}
static t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = (void *)content;
	list->next = NULL;
	return (list);
}
int main() {
	t_list *list = NULL;
	t_list *node1 = ft_lstnew((void *)1);
	t_list *node2 = ft_lstnew((void *)2);
	t_list *node3 = ft_lstnew((void *)3);

	ft_lstadd_front(&list, node1);
	ft_lstadd_front(&list, node2);
	ft_lstadd_front(&list, node3);

	print_list(list);

	return (0);
}*/
