/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:11:06 by cmarrued          #+#    #+#             */
/*   Updated: 2025/06/16 21:44:23 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_pwd(int outfd)
{
	char	cwd[1024];

	if (outfd == -1)
		outfd = 1;
	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putstr_fd(cwd, outfd);
		ft_putchar_fd('\n', outfd);
	}
	else
		return (1);
	return (0);
}
