/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intherna <intherna@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:49:22 by intherna          #+#    #+#             */
/*   Updated: 2025/06/28 17:08:29 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

uint8_t	g_sigint;

int	is_empty(t_state *state)
{
	return (state->pipeline.amount == 1
		&& state->pipeline.cmds[0]->argc == 0);
}

static uint_fast8_t	is_line_invalid(char *line)
{
	if (!*line)
	{
		free(line);
		return (1);
	}
	return (0);
}

void	main_loop(t_state *state)
{
	char	*line;
	char	*command;

	while (!state->end)
	{
		clean_pipeline(&state->pipeline);
		line = read_prompt();
		if (!line)
			break ;
		if (is_line_invalid(line))
			continue ;
		command = inject_env(line, state->env, state, &envchr);
		add_history(line);
		free(line);
		line = inject_astsk(command, state);
		if (!line || !*line || !parse_full_command(line, state)
			|| is_empty(state))
		{
			clean_return(line);
			continue ;
		}
		state->status = execute_pipeline(&state->pipeline, &state->env, state);
		free(line);
	}
}

static char	**init_env(char **envp, t_state *state)
{
	char	**env;

	if (!getcwd(state->pwd, sizeof(state->pwd)))
		ft_strlcpy(state->pwd, "/tmp", sizeof(state->pwd));
	if (!envp || !envp[0])
	{
		env = malloc(sizeof(char *) * 6);
		if (!env)
			return (NULL);
		env[0] = gen_pair("PWD", state->pwd);
		env[2] = ft_strdup("SHLVL=0");
		env[3] = ft_strdup("_=/usr/bin/env");
		env[4] = ft_strdup("PATH=/usr/bin:/bin");
		env[5] = NULL;
	}
	else
		env = copy_env(envp);
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	t_state	state;
	char	*tmp;

	g_sigint = 0;
	(void)argc;
	(void)argv;
	state = (t_state){0, {NULL, 0}, NULL, NULL, 0, "", ""};
	state.env = init_env(envp, &state);
	if (!state.env)
		return (print_error("Failed to initialize env", errno, 1, &state), 1);
	tmp = ft_itoa((ft_atoi(get_env("SHLVL", state.env, 0).str) + 1));
	set_env_value(&state.env, "SHLVL", tmp);
	free(tmp);
	ft_get_pid(state.pid);
	init_signals();
	main_loop(&state);
	clean_pipeline(&state.pipeline);
	rl_clear_history();
	free_env(state.env);
	ft_lstclear(&state.export_list, free);
	return (state.status);
}
