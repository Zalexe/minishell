/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:40:52 by cmarrued          #+#    #+#             */
/*   Updated: 2024/12/19 15:40:53 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		ln;
	int		i;
	char	*dp;

	ln = 0;
	i = 0;
	while (s[ln] != '\0')
		ln++;
	dp = (char *) malloc(ln + 1);
	if (dp == 0)
		return (0);
	while (s[i] != '\0')
	{
		dp[i] = s[i];
		i++;
	}
	dp[i] = '\0';
	return (dp);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*str = "hola buenos dias";
	char	*dp;	
	dp = ft_strdup(str);
	printf("%s\n", dp);
	return (0);
}*/
