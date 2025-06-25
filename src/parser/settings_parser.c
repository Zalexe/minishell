/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intherna <intherna@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:25:58 by intherna          #+#    #+#             */
/*   Updated: 2025/06/25 20:39:17 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

char	*skip_whitespaces(char *str)
{
	while (is_whitespace(*str))
		str++;
	return (str);
}

t_parse_result	parse_heredoc(t_cmd *cmd, char *str, t_state *state)
{
	t_slice			eof;
	uint_fast8_t	quote;

	quote = 1;
	str = str + 2;
	str = skip_whitespaces(str);
	close_safe(cmd->settings.pseudo_stdin);
	if (*str == '\'' || *str == '"')
		quote = 0;
	eof = get_arg(str, state);
	if (!eof.str)
		return ((t_parse_result){NULL, NULL});
	str += eof.len;
	str = skip_whitespaces(str);
	if (!*eof.str)
		cmd->settings.failed = (
				print_error("syntax error: unexpected token", 1, 1, state), 1);
	else if (!handle_heredoc(&cmd->settings, eof.str, quote, state))
		return (free(eof.str), (t_parse_result){NULL, NULL});
	free(eof.str);
	return ((t_parse_result){str, cmd});
}

t_parse_result	parse_in_redir(t_cmd *cmd, char *str, t_state *state)
{
	t_slice	file;

	close_safe(cmd->settings.pseudo_stdin);
	str++;
	str = skip_whitespaces(str);
	file = get_arg(str, state);
	if (!file.str)
		return ((t_parse_result){NULL, NULL});
	if (ft_strncmp(file.str, "*", 2) == 0)
		cmd->settings.failed = (
				print_error("ambiguous redirect", 1, 1, state), 1);
	else if (!*file.str)
		cmd->settings.failed = (
				print_error("syntax error: unexpected token", 1, 1, state), 1);
	else
		cmd->settings.pseudo_stdin = open(file.str, O_RDONLY);
	free(file.str);
	str += file.len;
	str = skip_whitespaces(str);
	if (cmd->settings.pseudo_stdin == -1 && !cmd->settings.failed)
		cmd->settings.failed = (print_error(NULL, errno, 1, state), 1);
	return ((t_parse_result){str, cmd});
}

t_parse_result	parse_out_redir(t_cmd *cmd, char *str, t_state *state)
{
	t_slice	arg;

	cmd->settings.is_append = 0;
	close_safe(cmd->settings.pseudo_stdout);
	if (*(str + 1) == '>')
		cmd->settings.is_append = 1;
	str = skip_whitespaces(str + 1 + cmd->settings.is_append);
	arg = get_arg(str, state);
	if (!arg.str)
		return ((t_parse_result){NULL, NULL});
	if (!validate_token(arg.str, state))
		cmd->settings.failed = 1;
	else if (cmd->settings.is_append)
		cmd->settings.pseudo_stdout = open(arg.str, O_CREAT
				| O_APPEND | O_WRONLY, 0644);
	else
		cmd->settings.pseudo_stdout = open(arg.str, O_CREAT
				| O_TRUNC | O_WRONLY, 0644);
	free(arg.str);
	str = skip_whitespaces(str + arg.len);
	if (cmd->settings.pseudo_stdout == -1 && !cmd->settings.failed)
		cmd->settings.failed = (print_error(NULL, errno, 1, state), 1);
	return ((t_parse_result){str, cmd});
}

t_parse_result	parse_symbols(t_cmd *cmd, char *str, t_state *state)
{
	t_parse_result	res;

	res = (t_parse_result){str, cmd};
	if (*str == '<' && *(str + 1) == '<')
	{
		res = parse_heredoc(cmd, str, state);
		if (res.command && !res.command->settings.failed)
			return (parse_symbols(res.command, res.end_pos, state));
	}
	else if (*str == '<')
	{
		res = parse_in_redir(cmd, str, state);
		if (res.command && !res.command->settings.failed)
			return (parse_symbols(res.command, res.end_pos, state));
	}
	else if (*str == '>')
	{
		res = parse_out_redir(cmd, str, state);
		if (res.command && !res.command->settings.failed)
			return (parse_symbols(res.command, res.end_pos, state));
	}
	return (res);
}
