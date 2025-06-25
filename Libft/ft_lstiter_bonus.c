/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:37:30 by cmarrued          #+#    #+#             */
/*   Updated: 2024/12/23 18:37:34 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
/*
#include <stdio.h>
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
static void print_content(void *content) {
	printf("Contenido: %d\n", *(int *)content);
}

static void print_list(t_list *lst) {
	if (lst != NULL)
		printf("Contenido del nodo: %d\n", *(int *)(lst->content));
	else
		printf("Lista vacía.\n");
}

int main() {
	int *data1 = (int *)malloc(sizeof(int));
	*data1 = 10;
	t_list *node1 = ft_lstnew(data1);
	int *data2 = (int *)malloc(sizeof(int));
	*data2 = 20;
	t_list *node2 = ft_lstnew(data2);
	node1->next = node2;

	int *data3 = (int *)malloc(sizeof(int));
	*data3 = 30;
	t_list *node3 = ft_lstnew(data3);
	node2->next = node3;
	
	printf("Lista antes de ft_lstiter:\n");
	print_list(node1);
	print_list(node2);
	print_list(node3);
	printf("\nAplicando ft_lstiter a la lista:\n");
	ft_lstiter(node1, print_content);
	free(data1);
	free(data2);
	free(data3);
	free(node1);
	free(node2);
	free(node3);
	return (0);
}*/
