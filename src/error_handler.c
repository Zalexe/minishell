/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intherna <intherna@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:31:04 by intherna          #+#    #+#             */
/*   Updated: 2025/06/19 21:18:38 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdint.h>
#include <string.h>
#include <unistd.h>

/**
 * msg: optional (nullable), message to print,
 * or NULL to print the corresponding error message for the code provided
 * code: error code
 */
void	print_error(char *msg, uint8_t code, uint8_t exit_code, t_state *state)
{
	write(2, "minishell: ", 11);
	if (msg == NULL)
		write(2, strerror(code), ft_strlen(strerror(code)));
	else
		write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	state->status = exit_code;
}

void	print_error_no_state(char *msg, uint8_t code)
{
	write(2, "minishell: ", 11);
	if (msg == NULL)
		write(2, strerror(code), ft_strlen(strerror(code)));
	else
		write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	*error_return(char *msg, uint8_t code,
			uint8_t exit_code, t_state *state)
{
	print_error(msg, code, exit_code, state);
	return (NULL);
}

void	close_safe(int fd)
{
	if (fd != -1)
		close(fd);
}
