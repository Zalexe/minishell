/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:08:37 by cmarrued          #+#    #+#             */
/*   Updated: 2024/12/20 17:08:38 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb < 10 && nb > -1)
	{
		ft_putchar_fd((nb + '0'), fd);
	}
	else if (nb > -10 && nb < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd((nb * -1 + '0'), fd);
	}
	else if (nb <= -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		ft_putnbr_fd(147483648, fd);
	}
	else
	{
		ft_putnbr_fd(nb / 10, fd);
		if (nb < 0)
			nb *= -1;
		ft_putnbr_fd(nb % 10, fd);
	}
}
/*
int	main(void)
{
	int	a;
	a = 151241231;
	ft_putnbr_fd(a, 1);
	return (0);
}*/
