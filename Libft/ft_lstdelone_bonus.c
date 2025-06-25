/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:20:35 by cmarrued          #+#    #+#             */
/*   Updated: 2024/12/23 18:20:37 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	(*del)(lst->content);
	free(lst);
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
void del(void *content) {
    free(content);
}

static void print_list(t_list *lst) {
	t_list *temp = lst;
	while (temp != NULL) {
		printf("%d \n", *(int *)temp->content);
		temp = temp->next;
	}
}

int main() {
	int *data = malloc(sizeof(int));
	*data = 42;
	t_list *node = ft_lstnew(data);
	print_list(node);
	ft_lstdelone(node, del);

	//printf("Después de ft_lstdelone:\n");
	//print_list(node); 
	//free(data);
	//free(node);
	return (0);
}*/
