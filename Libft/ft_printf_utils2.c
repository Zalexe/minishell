/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:05:53 by cmarrued          #+#    #+#             */
/*   Updated: 2025/01/07 18:05:56 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_printchar(char c)
{
	ssize_t	result;

	result = write(1, &c, 1);
	return (result);
}

int	ft_printstr(char *str)
{
	int		i;
	ssize_t	result;

	i = 0;
	if (!str)
	{
		str = "(null)";
	}
	while (str[i])
	{
		result = write(1, &str[i], 1);
		if (result < 0)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_printnbr(int nb)
{
	int		count;
	ssize_t	result;

	count = 0;
	if (nb < 10 && nb > -1)
		result = ft_printchar((nb + '0'));
	else if (nb > -10 && nb < 0)
		result = ft_printchar('-') + ft_printchar((nb * -1 + '0'));
	else if (nb <= -2147483648)
	{
		result = ft_printstr("-2");
		result += ft_printnbr(147483648);
	}
	else
	{
		result = ft_printnbr(nb / 10);
		if (nb < 0)
			nb *= -1;
		result += ft_printnbr(nb % 10);
	}
	if (result <= 0)
		return (-1);
	count += result;
	return (count);
}
