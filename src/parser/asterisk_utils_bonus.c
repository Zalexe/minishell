/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intherna <intherna@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:52:08 by intherna          #+#    #+#             */
/*   Updated: 2025/06/24 19:29:22 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*arg_astsk_chr(char *str)
{
	uint_fast8_t	quote;
	uint_fast8_t	double_quote;

	quote = 0;
	double_quote = 0;
	while (*str)
	{
		if (((*str == '<' && *(str + 1) == '<') || is_arg_delimiter(*str))
			&& !quote && !double_quote)
			return (NULL);
		if (*str == '*' && !quote && !double_quote)
			return (str);
		if (*str == '\'' && !double_quote)
			quote = !quote;
		if (*str == '"' && !quote)
			double_quote = !double_quote;
		str++;
	}
	return (NULL);
}

char	*astsk_chr(char *str)
{
	char	*tmp;

	while (*str)
	{
		tmp = arg_astsk_chr(str);
		if (tmp)
			break ;
		if (*str == '<' || *str == '>')
			str = skip_whitespaces(
					str + 1 + (*(str + 1) == '<' || *(str + 1) == '>'));
		str = argdelimitchr(str);
		while (*str && is_arg_delimiter(*str) && *str != '<' && *str != '>')
			str++;
	}
	if (!*str)
		return (NULL);
	return (str);
}

static int	len_until_next(char *str, char *pattern, char *astsk, char *end)
{
	char	*found;
	char	*pattern_clone;
	char	tmp;

	if (!astsk)
		astsk = end;
	tmp = *astsk;
	*astsk = '\0';
	pattern_clone = get_arg_astsk(pattern);
	if (!pattern_clone)
		return (ft_strlen(str));
	found = ft_strnstr(str, pattern_clone, SIZE_MAX);
	free(pattern_clone);
	*astsk = tmp;
	if (!found)
		return (ft_strlen(str));
	return (found - str);
}

static int	ft_strncmp_quote(char *patt, char *str, size_t size)
{
	char	*clone;
	int		res;
	int		quotecount;
	char	save;

	save = patt[size];
	patt[size] = '\0';
	quotecount = count_quotes(patt);
	clone = get_arg_astsk(patt);
	patt[size] = save;
	if (!clone)
		return (1);
	res = ft_strncmp(clone, str, size - quotecount);
	free(clone);
	return (res);
}

int	astsk_criteria(char *str, char *pattern)
{
	char			*end;
	char			*astsk;
	size_t			skip;

	end = argdelimitchr(pattern);
	end = rev_quotes(end, end - pattern);
	skip = 0;
	astsk = arg_astsk_chr(pattern);
	while (astsk)
	{
		while (is_consecutive_quote(pattern))
			pattern += 2;
		if (ft_strncmp_quote(pattern, str + skip, astsk - pattern) != 0)
			return (0);
		skip += (astsk - pattern);
		pattern = astsk + 1;
		pattern = skip_chars(pattern, '*');
		astsk = arg_astsk_chr(pattern);
		skip += len_until_next(str + skip, pattern, astsk, end);
	}
	if (pattern < end)
		if (ft_strncmp_quote(pattern, str + skip, end - pattern) != 0
			|| (str + skip + (end - pattern)) < (str + ft_strlen(str)))
			return (0);
	return (1);
}
