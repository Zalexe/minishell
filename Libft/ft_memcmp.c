/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:43:29 by cmarrued          #+#    #+#             */
/*   Updated: 2024/12/19 18:43:31 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(void *s1, void *s2, size_t n)
{
	size_t			l;
	unsigned char	*a1;
	unsigned char	*a2;	

	a1 = s1;
	a2 = s2;
	l = 0;
	while (l < n)
	{
		if (a1[l] > a2[l])
		{
			return (1);
		}
		else if (a1[l] < a2[l])
		{
			return (-1);
		}
		l++;
	}
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{

	int t = ft_memcmp("zeta", "delta", 3);	
	printf("%d\n", t);
	t = ft_memcmp("abc", "abc", 3);		
	printf("%d\n", t);
	t = ft_memcmp("apple", "apricot", 3);	
	printf("%d\n", t);
	return (0);
}*/
