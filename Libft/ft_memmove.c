/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:37:30 by cmarrued          #+#    #+#             */
/*   Updated: 2024/12/19 15:37:34 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	size_t			i;
	unsigned char	*a1;
	unsigned char	*a2;

	i = 0;
	a1 = (unsigned char *) dest;
	a2 = (unsigned char *) src;
	if (!dest && !src)
		return (NULL);
	if (a1 < a2 || (a1 >= (a2 + size)))
	{
		while (i < size)
		{
			a1[i] = a2[i];
			i++;
		}
	}
	else
	{
		while (size--)
			a1[size] = a2[size];
	}
	return (a1);
}
/*
#include <stdio.h>
int	main(void)
{
 
	char target[] = "a shiny white sphere";
	char * p = target + 8;  
	char * source = target + 2;

	printf( "Before memmove, target is \"%s\"\n", target );
	ft_memmove( p, source, 5 );
	printf( "After memmove, target becomes \"%s\"\n", target );
	return (0);
}*/
