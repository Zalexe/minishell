/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intherna <intherna@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:22:58 by intherna          #+#    #+#             */
/*   Updated: 2025/06/20 17:10:00 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_cmd_delimiter(char ch)
{
	return (ch == '|' || ch == '\0');
}

int	is_arg_delimiter(char ch)
{
	return (ch == '<' || ch == '>'
		|| ch == '|' || is_whitespace(ch));
}

/**
 * Same behavior as ft_strchr, except it will return the pointer to the
 * next valid argument delimiter character, 
 * which could be whitespace (is_whitespace(char c)), |, <, >
 */
char	*argdelimitchr(char *str)
{
	uint_fast8_t	quote;
	uint_fast8_t	double_quote;

	quote = 0;
	double_quote = 0;
	while (*str)
	{
		if (is_arg_delimiter(*str) && !quote && !double_quote)
			return (str);
		if (*str == '\'' && !double_quote)
			quote = !quote;
		if (*str == '"' && !quote)
			double_quote = !double_quote;
		str++;
	}
	return (str);
}

char	*cmddelimitchr(char *str)
{
	uint_fast8_t	quote;
	uint_fast8_t	double_quote;

	quote = 0;
	double_quote = 0;
	while (*str)
	{
		if (is_cmd_delimiter(*str) && !quote && !double_quote)
			return (str);
		if (*str == '\'' && !double_quote)
			quote = !quote;
		if (*str == '"' && !quote)
			double_quote = !double_quote;
		str++;
	}
	return (str);
}
