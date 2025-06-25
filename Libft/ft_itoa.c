/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:04:00 by cmarrued          #+#    #+#             */
/*   Updated: 2025/01/02 18:30:56 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	ft_intlen(long nb)
{
	size_t	count;

	count = 0;
	if (nb <= 0)
	{
		count++;
	}
	while (nb != 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*strn;
	size_t	ln;
	long	nb;

	nb = n;
	ln = ft_intlen(nb);
	strn = (char *)malloc(sizeof(char) * (ln + 1));
	if (!strn)
		return (NULL);
	if (nb == 0)
		strn[0] = '0';
	else if (nb < 0)
	{
		strn[0] = '-';
		nb = -nb;
	}
	strn[ln] = '\0';
	while (nb != 0 && ln--)
	{
		strn[ln] = (nb % 10) + '0';
		nb /= 10;
	}
	return (strn);
}
/*
#include <stdio.h>
int	main(void)
{
	int s = 675464;
	int d = -1341511;
	int e = 0;
	printf("%s\n",ft_itoa(s));
	printf("%s\n",ft_itoa(d));
	printf("%s\n",ft_itoa(e));
	return (0);
}*/
