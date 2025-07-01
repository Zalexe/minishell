/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:41:14 by cmarrued          #+#    #+#             */
/*   Updated: 2025/06/30 17:58:53 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "type_utils.h"
#include <stdlib.h>

static t_parse_result	build_args(t_cmd *cmd, char *end_pos, t_state *state)
{
	cmd->args = malloc(sizeof(char *) * (cmd->argc + 1));
	if (!cmd->args)
		return (print_error(NULL, errno, 1, state),
			(t_parse_result){end_pos, cmd});
	cmd->args[cmd->argc] = NULL;
	return ((t_parse_result){end_pos, cmd});
}

static t_parse_result	rec_parse(t_cmd *cmd, char *str, t_state *state)
{
	t_parse_vars	v;

	str = skip_whitespaces(str);
	v.res = parse_symbols(cmd, str, state);
	if (!v.res.end_pos || !v.res.command || cmd->settings.failed)
		return (v.res);
	str = v.res.end_pos;
	if (is_cmd_delimiter(*str))
		return (build_args(cmd, str, state));
	v.arg = get_arg(str, state);
	if (!v.arg.str)
		return (clean_cmd(cmd), (t_parse_result){NULL, NULL});
	str += v.arg.len;
	v.pos = cmd->argc++;
	v.res = rec_parse(cmd, str, state);
	if (!v.res.command || !v.res.command->args)
	{
		free(v.arg.str);
		if (!v.res.end_pos)
			return ((t_parse_result){NULL, NULL});
		v.res.end_pos = cmddelimitchr(v.res.end_pos);
	}
	else
		cmd->args[v.pos] = v.arg.str;
	return (v.res);
}

t_parse_result	parse_command(char *cmd, t_state *state)
{
	t_cmd			*res;
	t_parse_result	final;

	if (*cmd == '|')
		return (print_error("syntax error: invalid character near |",
				0, 2, state), (t_parse_result){NULL, NULL});
	res = malloc(sizeof(t_cmd));
	if (!res)
		return (print_error(NULL, errno, 1, state),
			(t_parse_result){cmd, NULL});
	res->args = NULL;
	res->argc = 0;
	settings_zero(&res->settings);
	final = rec_parse(res, cmd, state);
	return (final);
}

int	parse_full_command(char *str, t_state *state)
{
	t_parse_result	actual_res;
	int				res;
	int				pos;

	if (*str == '\0')
	{
		state->pipeline.cmds = malloc(sizeof(t_cmd *) * state->pipeline.amount);
		return (state->pipeline.cmds != NULL);
	}
	actual_res = parse_command(str, state);
	if (!actual_res.end_pos)
		return (0);
	str = actual_res.end_pos;
	pos = state->pipeline.amount++;
	if (*str == '|')
		str++;
	str = skip_whitespaces(str);
	res = parse_full_command(str, state);
	if (!res)
		return (clean_cmd(actual_res.command));
	state->pipeline.cmds[pos] = actual_res.command;
	return (res);
}
