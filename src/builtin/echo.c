/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:10:51 by cmarrued          #+#    #+#             */
/*   Updated: 2025/06/16 21:38:15 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	is_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 1;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

int	ft_echo(char **args, int outfd)
{
	int		i;
	int		newline;

	if (outfd == -1)
		outfd = 1;
	i = 1;
	newline = 1;
	while (args[i] && is_n_option(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		write(outfd, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(outfd, " ", 1);
		i++;
	}
	if (newline)
		write(outfd, "\n", 1);
	return (0);
}
