/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:24:37 by cmarrued          #+#    #+#             */
/*   Updated: 2025/01/04 15:24:39 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_putnbr_unsigned(unsigned int n)
{
	int	count;
	int	result;

	count = 0;
	if (n >= 10)
	{
		result = ft_putnbr_unsigned(n / 10);
		result += ft_printchar(((n % 10) + '0'));
	}
	else
		result = ft_printchar(n + '0');
	count += result;
	if (result < 0)
		return (-1);
	return (count);
}

int	ft_putnbr_hex(unsigned long n, int uppercase)
{
	int		count;
	int		result;
	char	*base;

	count = 0;
	base = "0123456789abcdef";
	if (uppercase)
		base = "0123456789ABCDEF";
	if (n >= 16)
	{
		result = ft_putnbr_hex(n / 16, uppercase);
		result += ft_printchar(base[n % 16]);
	}
	else
		result = ft_printchar(base[n]);
	count += result;
	if (result < 0)
		return (-1);
	return (count);
}

int	ft_putpointer(unsigned long nb)
{
	int	result;

	if (!nb)
		return (ft_printstr("(nil)"));
	result = ft_printstr("0x") + ft_putnbr_hex(nb, 0);
	if (result < 0)
		return (-1);
	return (result);
}
