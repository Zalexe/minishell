/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intherna <intherna@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:49:22 by intherna          #+#    #+#             */
/*   Updated: 2025/06/22 18:31:20 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		command = inject_env(line, state->env, state->status, &envchr);
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

static char	**init_env(char **envp)
{
	char	**env;
	char	cwd[PATH_MAX];

	if (!envp || !envp[0])
	{
		env = malloc(sizeof(char *) * 6);
		if (!env)
			return (NULL);
		if (!getcwd(cwd, sizeof(cwd)))
			ft_strlcpy(cwd, "/tmp", sizeof(cwd));
		env[0] = gen_pair("PWD", cwd);
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
	char	**shell_env;
	t_state	state;
	char	*tmp;

	g_sigint = 0;
	(void)argc;
	(void)argv;
	shell_env = init_env(envp);
	if (!shell_env)
		return (print_error("Failed to initialize env", errno, 1, &state), 1);
	tmp = ft_itoa((ft_atoi(get_env("SHLVL", shell_env, 0).str) + 1));
	set_env_value(&shell_env, "SHLVL", tmp);
	free(tmp);
	state = (t_state){0, {NULL, 0}, shell_env, NULL, 0};
	init_signals();
	main_loop(&state);
	clean_pipeline(&state.pipeline);
	rl_clear_history();
	free_env(state.env);
	ft_lstclear(&state.export_list, free);
	return (state.status);
}
