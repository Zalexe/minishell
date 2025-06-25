/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intherna <intherna@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:38:08 by intherna          #+#    #+#             */
/*   Updated: 2025/06/23 19:04:44 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	*clean_return(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	settings_zero(t_cmd_settings *set)
{
	set->pseudo_stdin = -1;
	set->pseudo_stdout = -1;
	set->is_append = 0;
	set->failed = 0;
	set->heredoc = 0;
}

int	clean_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return (0);
	i = 0;
	if (cmd->args)
	{
		while (i < cmd->argc)
			free(cmd->args[i++]);
		free(cmd->args);
	}
	free(cmd);
	return (0);
}

int	clean_pipeline(t_pipeline *pipe)
{
	int	i;

	i = 0;
	while (i < pipe->amount)
	{
		if (pipe->cmds == NULL)
			break ;
		clean_cmd(pipe->cmds[i++]);
	}
	clean_return(pipe->cmds);
	pipe->cmds = NULL;
	pipe->amount = 0;
	return (0);
}

int	validate_token(char *str, t_state *state)
{
	if (ft_strncmp(str, "*", 2) == 0)
		return (print_error("ambiguous redirect", 1, 1, state), 0);
	else if (!*str)
		return (print_error("syntax error: unexpected token", 1, 1, state), 0);
	return (1);
}
