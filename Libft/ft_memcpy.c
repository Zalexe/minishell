/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:37:23 by cmarrued          #+#    #+#             */
/*   Updated: 2024/12/19 15:37:25 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	size_t			i;
	unsigned char	*a1;
	unsigned char	*a2;

	if (!dest && !src)
		return (NULL);
	i = 0;
	a1 = (unsigned char *) dest;
	a2 = (unsigned char *) src;
	while (i < size)
	{
		a1[i] = a2[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
int	main(void)
{
	char dest1[50] = "Initial string in destination";
	char src1[] = "This is a test";

	printf("Before ft_memcpy (no overlap), dest1: \"%s\"\n", dest1);
	ft_memcpy(dest1 + 10, src1, 14);
	printf("After ft_memcpy (no overlap), dest1: \"%s\"\n", dest1);
	return (0);
}*/
