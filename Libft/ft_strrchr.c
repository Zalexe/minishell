/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:39:25 by cmarrued          #+#    #+#             */
/*   Updated: 2024/12/19 15:39:27 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;

	i = ft_strlen(str) + 1;
	while (i--)
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	char	string[64] ="This is a test string for testing strrchr";
	char	*p;

	p = ft_strrchr(string,'e');
	if (p)
	{
		printf("Char found:\n" );

		printf ("Last occurrence of char \"e\" in \"%s\" is:\n%s", string, p);
	}
	else
	{
		printf("Char not found!\n" );
	}

	return 0;
}*/
