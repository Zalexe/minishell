/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:11:13 by cmarrued          #+#    #+#             */
/*   Updated: 2025/06/07 20:22:49 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	remove_env_entry(char ***env, const char *key)
{
	int		i;
	int		j;
	int		len;
	char	**e;

	e = *env;
	len = ft_strlen(key);
	i = -1;
	while (e[++i])
	{
		if (ft_strncmp(e[i], key, len) == 0 && e[i][len] == '=')
		{
			free(e[i]);
			j = i - 1;
			while (e[++j])
				e[j] = e[j + 1];
			return ;
		}
	}
}

void	remove_from_export_list(t_list **list, const char *key)
{
	t_list	*prev;
	t_list	*curr;

	prev = NULL;
	curr = *list;
	while (curr)
	{
		if (ft_strncmp((char *)curr->content, key, ft_strlen(key)) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*list = curr->next;
			free(curr->content);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	ft_unset(char **args, char ***env, t_state *state)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_env_entry(env, args[i]);
		remove_from_export_list(&state->export_list, args[i]);
		i++;
	}
	return (0);
}
