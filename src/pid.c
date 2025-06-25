/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intherna <intherna@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:45:02 by intherna          #+#    #+#             */
/*   Updated: 2025/06/25 19:50:24 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

void	ft_get_pid(char buffer[10])
{
	char	byte;
	int		fd;
	int		i;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
	{
		buffer[0] = '\0';
		return ;
	}
	byte = '-';
	i = 0;
	while (1)
	{
		if (read(fd, buffer + i, 1) == -1)
			break ;
		byte = buffer[i];
		if (!byte || byte == ' ')
			break ;
		i++;
	}
	buffer[i] = '\0';
}
