/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:07:17 by cmarrued          #+#    #+#             */
/*   Updated: 2024/12/20 17:07:18 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
			write(fd, &s[i++], 1);
	}
}
/*
int	main(void)
{
	char *a;
	a = "asdadassa";
	ft_putstr_fd(a, 1);
	return (0);
}*/
