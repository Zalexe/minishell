/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:06:03 by cmarrued          #+#    #+#             */
/*   Updated: 2024/12/23 18:06:05 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
/*
#include <stdio.h>
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}
t_list	*ft_lstnew(void *content)
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

	int *data1 = malloc(sizeof(int));
	*data1 = 1;
	t_list *node1 = ft_lstnew((void *)data1);

	int *data2 = malloc(sizeof(int));
	*data2 = 2;
	t_list *node2 = ft_lstnew((void *)data2);

	int *data3 = malloc(sizeof(int));
	*data3 = 3;
	t_list *node3 = ft_lstnew((void *)data3);


	ft_lstadd_back(&list, node1);
	ft_lstadd_back(&list, node2);
	ft_lstadd_back(&list, node3);

	printf("%d -> ", *(int *)((ft_lstlast(list))->content));
	free(data1);
	free(data2);
	free(data3);
	free(node1);
	free(node2);
	free(node3);

	return (0);
}*/
