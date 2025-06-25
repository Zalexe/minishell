/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:24:25 by cmarrued          #+#    #+#             */
/*   Updated: 2025/06/14 20:10:53 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static long long	ft_atoll(const char *str)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	while (is_whitespace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
		res = res * 10 + (*str++ - '0');
	return (res * sign);
}

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_cmd *cmd, t_state *state, uint_fast8_t end)
{
	long long	code;

	if (end)
		ft_printf("exit\n");
	if (cmd->argc == 1)
	{
		state->end = 1;
		exit(state->status);
	}
	if (!is_numeric(cmd->args[1]))
	{
		print_error("exit: numeric argument required", 0, 2, state);
		exit(2);
	}
	if (cmd->argc > 2)
	{
		print_error("exit: too many arguments", 0, 1, state);
		state->status = 1;
		return ;
	}
	code = ft_atoll(cmd->args[1]);
	exit((unsigned char)code);
}
