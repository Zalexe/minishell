/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:09:47 by cmarrued          #+#    #+#             */
/*   Updated: 2024/12/23 18:09:49 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (*lst)
		(ft_lstlast(*lst))->next = new;
	else
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

	ft_lstadd_back(&list, node1);
	ft_lstadd_back(&list, node2);
	ft_lstadd_back(&list, node3);

	print_list(list);

	return (0);
}*/
