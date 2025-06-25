/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk_quote_handler_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intherna <intherna@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:36:11 by intherna          #+#    #+#             */
/*   Updated: 2025/06/23 20:59:45 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

uint_fast8_t	is_consecutive_quote(char *str)
{
	return ((*str == '"' && *(str + 1) == '"')
		|| (*str == '\'' && *(str + 1) == '\''));
}

char	*rev_quotes(char *str, size_t len)
{
	while (len > 1 && is_consecutive_quote(str - 2))
	{
		str -= 2;
		len -= 2;
	}
	return (str);
}

/**
* Shift characters to the left when quotes are found.
*/
char	*shift_quotes_astsk(char *str)
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
		return (NULL);
	return (str);
}

/**
* Aux function.
*/
static t_slice	get_arg_aux_astsk(char *str)
{
	char	*end;
	char	*res;
	size_t	size;

	end = argdelimitchr(str);
	size = end - str;
	res = malloc(size + 1);
	if (!res)
		return ((t_slice){NULL, 0});
	ft_memcpy(res, str, size);
	res[size] = '\0';
	if (!shift_quotes_astsk(res))
		return ((t_slice){clean_return(res), 0});
	return ((t_slice){res, size});
}

char	*get_arg_astsk(char *str)
{
	while (is_whitespace(*str))
		str++;
	return (get_arg_aux_astsk(str).str);
}
