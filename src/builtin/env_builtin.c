/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:10:42 by cmarrued          #+#    #+#             */
/*   Updated: 2025/06/16 21:40:23 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_env(char **env, int outfd)
{
	int	i;

	i = 0;
	if (outfd == -1)
		outfd = 1;
	while (env[i])
	{
		ft_putstr_fd(env[i], outfd);
		ft_putchar_fd('\n', outfd);
		i++;
	}
	return (0);
}
