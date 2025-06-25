/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 11:42:45 by cmarrued          #+#    #+#             */
/*   Updated: 2025/01/02 18:31:19 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*newnode;

	if (f == NULL || del == NULL)
		return (NULL);
	newlst = NULL;
	while (lst != NULL)
	{
		newnode = ft_lstnew(f(lst->content));
		if (!newnode)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, newnode);
		lst = lst->next;
	}
	return (newlst);
}
/*
#include <stdio.h>
static void *addone(void *content)
{
	int *new_content = malloc(sizeof(int));
	if (!new_content) return NULL;
	*new_content = *(int *)content + 1;
	return new_content;
}
static void del(void *content)
{
	free(content);
}
static void print_list(t_list *lst) {
	t_list *temp = lst;
	while (temp != NULL) {
		printf("%d \n", *(int *)temp->content);
		temp = temp->next;
	}
	printf("NULL\n");
}
int main()
{
	int *value1 = malloc(sizeof(int));
	int *value2 = malloc(sizeof(int));
	int *value3 = malloc(sizeof(int));
	*value1 = 1;
	*value2 = 2;
	*value3 = 3;

	t_list *lst = ft_lstnew(value1);
	ft_lstadd_back(&lst, ft_lstnew(value2));
	ft_lstadd_back(&lst, ft_lstnew(value3));
	printf("Lista original: ");
	print_list(lst);
	t_list *new_lst = ft_lstmap(lst, addone, del);

	printf("Lista después de ft_lstmap (+1): ");
	print_list(new_lst);

	ft_lstclear(&lst, del);
	ft_lstclear(&new_lst, del);

	return (0);
}*/
