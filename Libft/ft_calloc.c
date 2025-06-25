/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:35:16 by cmarrued          #+#    #+#             */
/*   Updated: 2025/01/02 18:05:00 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (SIZE_MAX / size < nmemb)
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, (nmemb * size));
	return (ptr);
}
/*
#include <stdio.h>
int	main(void)
{
	size_t num_elements = 10;
	size_t element_size = sizeof(int);
	int *arr = (int *)ft_calloc(num_elements, element_size);
	if (arr == NULL) {
		printf("Memory allocation failed\n");
		return 1;
	}
	printf("Allocated memory values (initialized to 0):\n");
	for (size_t i = 0; i < num_elements; i++) {
		printf("arr[%zu] = %d\n", i, arr[i]);
	}
	free(arr);
	return (0);
}*/
