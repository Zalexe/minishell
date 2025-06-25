/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 19:11:07 by cmarrued          #+#    #+#             */
/*   Updated: 2025/06/17 20:41:46 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

static char	*build_full_path(const char *dir, const char *cmd)
{
	char	*full;
	size_t	len_dir;
	size_t	len_cmd;

	len_dir = ft_strlen(dir);
	len_cmd = ft_strlen(cmd);
	full = malloc(len_dir + len_cmd + 2);
	if (!full)
		return (NULL);
	full[0] = '\0';
	ft_strlcat(full, dir, len_dir + 1);
	ft_strlcat(full, "/", len_dir + 2);
	ft_strlcat(full, cmd, len_dir + len_cmd + 2);
	return (full);
}

char	*get_command_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	char	*full;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = get_env("PATH", env, 0).str;
	if (!*path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full = build_full_path(paths[i], cmd);
		if (!full)
			return (free_paths(paths), NULL);
		if (access(full, X_OK) == 0)
			return (free_paths(paths), full);
		free(full);
	}
	free_paths(paths);
	return (NULL);
}
