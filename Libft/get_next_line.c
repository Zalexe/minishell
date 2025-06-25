/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:49:19 by cmarrued          #+#    #+#             */
/*   Updated: 2025/01/10 17:49:21 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*obtain_remain(char *b_buffer)
{
	char	*remain;
	int		i;
	int		j;

	i = 0;
	while (b_buffer[i] && b_buffer[i] != '\n')
		i++;
	if (!b_buffer[i])
	{
		free(b_buffer);
		return (NULL);
	}
	remain = ft_calloc((ft_strlen(b_buffer) - i + 1), sizeof(char));
	if (!remain)
		return (NULL);
	i++;
	j = 0;
	while (b_buffer[i])
		remain[j++] = b_buffer[i++];
	free(b_buffer);
	return (remain);
}

char	*extract_line(char *b_buffer)
{
	char	*temp;
	int		i;

	i = 0;
	if (!b_buffer[i])
		return (NULL);
	while (b_buffer[i] && b_buffer[i] != '\n')
		i++;
	temp = ft_calloc(i + 2, sizeof(char));
	if (!temp)
		return (NULL);
	i = 0;
	while (b_buffer[i] && b_buffer[i] != '\n')
	{
		temp[i] = b_buffer[i];
		i++;
	}
	if (b_buffer[i] && b_buffer[i] == '\n')
		temp[i++] = '\n';
	return (temp);
}

char	*append_buffer(char *b_buffer, char *read_buffer)
{
	char	*temp;

	temp = ft_strjoin(b_buffer, read_buffer);
	free(b_buffer);
	return (temp);
}

char	*read_from_file(char *b_buffer, int fd)
{
	int		bytes_read;
	char	*c_buffer;

	if (!b_buffer)
		b_buffer = ft_calloc(1, 1);
	c_buffer = ft_calloc (BUFFER_SIZE + 1, sizeof(char));
	if (!c_buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, c_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(c_buffer), NULL);
		c_buffer[bytes_read] = 0;
		b_buffer = append_buffer(b_buffer, c_buffer);
		if (ft_strchr(c_buffer, '\n'))
			break ;
	}
	free(c_buffer);
	return (b_buffer);
}

char	*get_next_line(int fd)
{
	static char	*b_buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	b_buffer = read_from_file(b_buffer, fd);
	if (!b_buffer)
		return (NULL);
	line = extract_line(b_buffer);
	b_buffer = obtain_remain(b_buffer);
	return (line);
}
