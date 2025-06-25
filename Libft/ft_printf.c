/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:29:55 by cmarrued          #+#    #+#             */
/*   Updated: 2024/12/28 16:29:57 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_printf(char const *format, ...)
{
	va_list	args;
	int		count;
	int		i;
	int		result;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	count = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
			result = handle_conversion(args, format[++i]);
		else
			result = ft_printchar(format[i]);
		count += result;
		if (result < 0)
			return (-1);
		i++;
	}
	va_end(args);
	return (count);
}
