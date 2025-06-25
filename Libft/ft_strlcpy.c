/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:37:54 by cmarrued          #+#    #+#             */
/*   Updated: 2024/12/19 15:37:56 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	ln;

	i = 0;
	if (!src)
		return (0);
	ln = ft_strlen(src);
	if (size == 0)
		return (ln);
	while (src[i] != '\0' && (i < size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ln);
}
/*
#include <stdio.h>
int	main(void)
{
	char	s2[8] = "abcdefg";
	char	s1[8];

	ft_strlcpy(s1, s2, 5);
	printf("s2=%s\n", s2 );
	printf("s1=%s\n", s1 );
	return (0);
}*/
