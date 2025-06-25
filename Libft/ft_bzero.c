/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:35:02 by cmarrued          #+#    #+#             */
/*   Updated: 2024/12/19 15:35:04 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_bzero(void *s, size_t size)
{
	size_t			i;
	unsigned char	*byte_ptr;

	byte_ptr = (unsigned char *)s;
	i = 0;
	while (i < size)
	{
		byte_ptr[i] = '\0';
		i++;
	}
}
/*
#include <stdio.h>
int	main(void)
{
	char str[] = "Hello, World!";
	printf("Before ft_bzero: %s\n", str);
	ft_bzero(str, 5); printf("After ft_bzero: ");
	for (int i = 0; i < 10; i++) {
		printf("\\x%02x ", (unsigned char)str[i]);
	}
	return (0);
}*/
