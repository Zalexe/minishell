/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:39:09 by cmarrued          #+#    #+#             */
/*   Updated: 2024/12/19 15:39:10 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	a;

	a = c;
	while (*str)
	{
		if (*str == a)
			return ((char *)str);
		str++;
	}
	if (a == '\0')
		return ((char *)str);
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	char	string[64] ="This is a test string for testing strchr";
	char	*p;

	p = ft_strchr(string,'a');
	if (p)
	{
		printf("Char found:\n" );

		printf ("1st occurrence of char \"a\" in \"%s\" is:\n%s", string, p);
	}
	else
	{
		printf("Char not found!\n" );
	}

	return 0;
}*/
