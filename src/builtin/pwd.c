/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:11:06 by cmarrued          #+#    #+#             */
/*   Updated: 2025/06/28 16:50:59 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_pwd(int outfd, t_state *state)
{
	if (outfd == -1)
		outfd = 1;
	ft_putstr_fd(state->pwd, outfd);
	ft_putchar_fd('\n', outfd);
	return (0);
}
