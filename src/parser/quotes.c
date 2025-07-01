/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:41:19 by cmarrued          #+#    #+#             */
/*   Updated: 2025/06/30 17:33:43 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

char	*skip_chars(char *str, char ch)
{
	while (*str == ch)
		str++;
	return (str);
}

int	count_quotes(char *str)
{
	int				quotes;
	uint_fast8_t	quote;
	uint_fast8_t	quote_double;

	quote = 0;
	quote_double = 0;
	quotes = 0;
	while (*str)
	{
		if (*str == '\'' && !quote_double)
		{
			quote = !quote;
			quotes++;
		}
		else if (*str == '"' && !quote)
		{
			quote_double = !quote_double;
			quotes++;
		}
		str++;
	}
	return (quotes);
}

/**
* Shift characters to the left when quotes are found.
*/
char	*shift_quotes(char *str, t_state *state)
{
	char	quote;
	int		shift;

	quote = '\0';
	shift = 0;
	while (*str)
	{
		if (((*str == '\'' || *str == '"') && !quote) || *str == quote)
		{
			if (!quote)
				quote = *str;
			else
				quote = '\0';
			shift++;
			str++;
			continue ;
		}
		*(str - shift) = *str;
		str++;
	}
	*(str - shift) = '\0';
	if (quote)
		return (error_return("syntax error: unclosed quotes", 1, 1, state));
	return (str);
}

/**
* Aux function.
*/
static t_slice	get_arg_aux(char *str, t_state *state)
{
	char	*res;
	char	*end;
	size_t	size;

	end = argdelimitchr(str);
	size = end - str;
	res = malloc(size + 1);
	if (!res)
		return ((t_slice){error_return(NULL, errno, 1, state), 0});
	ft_memcpy(res, str, size);
	res[size] = '\0';
	if (!shift_quotes(res, state))
		return ((t_slice){clean_return(res), 0});
	return ((t_slice){res, size});
}

t_slice	get_arg(char *str, t_state *state)
{
	while (is_whitespace(*str))
		str++;
	return (get_arg_aux(str, state));
}
