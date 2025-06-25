/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:03:22 by cmarrued          #+#    #+#             */
/*   Updated: 2025/01/02 18:25:59 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	check_sep(char c, char const *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*string;
	int		start;
	int		end;	
	int		i;

	start = 0;
	while (s1[start] && check_sep(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && check_sep(s1[end - 1], set))
		end--;
	string = (char *)malloc(sizeof(char) * (end - start + 1));
	if (string == 0)
		return (NULL);
	i = 0;
	while (start < end)
		string[i++] = s1[start++];
	string[i] = '\0';
	return (string);
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	char	*trim;
	(void)	argc;
	trim = ft_strtrim(argv[1], argv[2]);
	printf("%s\n", trim);
	free(trim);
	return (0);
}*/
