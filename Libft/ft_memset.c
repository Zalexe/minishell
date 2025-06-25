/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:37:14 by cmarrued          #+#    #+#             */
/*   Updated: 2024/12/19 15:37:15 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t size)
{
	size_t			i;
	unsigned char	*byte_ptr;

	byte_ptr = (unsigned char *)s;
	i = 0;
	while (i < (size))
	{
		byte_ptr[i] = (unsigned char) c;
		i++;
	}
	return (byte_ptr);
}
/*
#include <stdio.h>
int	main(void)
{
	char str[50] = "Hello, this is a test for ft_memset function!";
	printf("Before: %s\n", str);
	ft_memset(str, 'X', 5);
	printf("After: %s\n", str);
	return (0);
}*/
