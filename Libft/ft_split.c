/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:03:32 by cmarrued          #+#    #+#             */
/*   Updated: 2025/01/02 18:29:42 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == c)
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && str[i] != c)
			i++;
	}
	return (count);
}

static char	*ft_word(char *str, char c)
{
	int		len_word;
	int		i;
	char	*word;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	len_word = i;
	i = 0;
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	if (!word)
		return (NULL);
	while (i < len_word)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	free_strings(char **strings, int i)
{
	while (i > 0)
	{
		i--;
		free(strings[i]);
	}
	free(strings);
}

static char	**ft_split_while(char *str, char **strings, char c, int i)
{
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
		{
			strings[i] = ft_word((char *)str, c);
			if (strings[i] == NULL)
			{
				free_strings(strings, i);
				return (NULL);
			}
			i++;
		}
		while (*str && *str != c)
			str++;
	}
	strings[i] = NULL;
	return (strings);
}

char	**ft_split(char const *str, char c)
{
	char	**strings;
	int		i;

	i = 0;
	strings = (char **)malloc(sizeof(char *) * (count((char *)str, c) + 1));
	if (!strings)
		return (NULL);
	strings = ft_split_while((char *)str, strings, c, i);
	return (strings);
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	int		index;
	char	**split;
	(void)	argc;
	split = ft_split(argv[1], argv[2][0]);
	index = 0;
	while (split[index])
	{
		printf("%s\n", split[index]);
		index++;
	}
	index = 0;
	while (split[index])
	{
		free(split[index]);
		index++;
	}
	free(split);
}*/
