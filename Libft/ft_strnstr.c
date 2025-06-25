/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:40:28 by cmarrued          #+#    #+#             */
/*   Updated: 2025/06/19 19:28:05 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*to_find == '\0')
		return ((char *)str);
	while (str[i] != 0 && i < len)
	{
		if (str[i] == to_find[0])
		{
			j = 0;
			while (str[i + j] == to_find[j] && (i + j) < len)
			{
				j++;
				if (to_find[j] == '\0')
					return ((char *)(str + i));
			}
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	char	string[64] ="This is a test string for testing strstr";
	char	*p;

	p = ft_strnstr(string,"test", 10);
	if (p)
	{
		printf("String found:\n" );

		printf ("1st occurrence of st \"test\" in \"%s\" is:\n%s", string, p);
	}
	else
	{
		printf("String not found!\n" );
	}

	return 0;
}*/
