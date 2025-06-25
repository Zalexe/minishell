/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:05:03 by cmarrued          #+#    #+#             */
/*   Updated: 2024/12/20 17:05:04 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
int	main(void)
{
	char a, b ,c;
	a = 'a';
	b = '1';
	c = '!';
	ft_putchar_fd(a, 1);
	ft_putchar_fd(b, 1);
	ft_putchar_fd(c, 1);
	return (0);
}*/
