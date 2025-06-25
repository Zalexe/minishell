/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:40:10 by cmarrued          #+#    #+#             */
/*   Updated: 2024/12/19 15:40:11 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(void *s, int c, size_t size)
{
	size_t			i;	
	unsigned char	*byte_ptr;

	byte_ptr = (unsigned char *)s;
	i = 0;
	while (i < size)
	{
		if (*byte_ptr == (unsigned char)c)
			return (byte_ptr);
		byte_ptr++;
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	char str[] = "Hello, World!";
	char c = 'o';
	char *result = (char *)ft_memchr(str, c, sizeof(str));
	
	if (result != NULL)
		printf("Encontrado '%c' en la posición: %ld\n", c, result - str);
	else
		printf("El carácter '%c' no se encontró.\n", c);

	return (0);
}*/
