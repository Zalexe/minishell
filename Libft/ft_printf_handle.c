/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:24:50 by cmarrued          #+#    #+#             */
/*   Updated: 2025/01/04 15:24:52 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	handle_conversion(va_list args, char c)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_printchar(va_arg(args, int));
	else if (c == 's')
		count += ft_printstr(va_arg(args, char *));
	else if (c == 'p')
		count += ft_putpointer(va_arg(args, unsigned long long));
	else if (c == 'd' || c == 'i')
		count += ft_printnbr(va_arg(args, int));
	else if (c == 'u')
		count += ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (c == 'x' || c == 'X')
		count += ft_putnbr_hex(va_arg(args, unsigned int), (c == 'X'));
	else if (c == '%')
		count += ft_printchar('%');
	return (count);
}
