/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:08:24 by cmarrued          #+#    #+#             */
/*   Updated: 2024/12/20 17:08:26 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int		i;
	char	c;

	i = 0;
	c = '\n';
	if (s)
	{
		while (s[i] != '\0')
			write(fd, &s[i++], 1);
	}
	write(fd, &c, 1);
}
/*
int	main(void)
{
	char *a;
	a = "asdadassa";
	ft_putendl_fd(a, 1);
	return (0);
}*/
