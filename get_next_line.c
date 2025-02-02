/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpineda- <kpineda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:08:36 by kpineda-          #+#    #+#             */
/*   Updated: 2025/02/02 17:18:16 by kpineda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_split_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	while (buffer[i] != '\0' && buffer[i++] != '\n')
		;
	if (buffer[i] == '\0')
		return (ft_strdup(buffer));
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		line[i] = buffer[i];
		i++;
		if (buffer[i] == '\n')
			line[i] = buffer[i];
	}
	if (buffer[i] == '\n')
		line[i] = buffer[i];
	line[++i] = '\0';
	return (line);
}

static char	*get_line(int fd, char *buffer, char *temp_buffer)
{
	int	bytes_read;

	bytes_read = 1;
	while (!ft_strchr(temp_buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(temp_buffer), free(buffer), NULL);
		temp_buffer[bytes_read] = '\0';
		if (bytes_read)
			buffer = ft_strjoin(buffer, temp_buffer);
		if (!ft_strlen(buffer))
			return (free(temp_buffer), free(buffer), NULL);
	}
	free(temp_buffer);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*temp_buffer;
	char		*line;
	int			line_len;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 0;
	temp_buffer = malloc(BUFFER_SIZE + 1);
	if (!temp_buffer)
		return (NULL);
	temp_buffer[0] = '\0';
	buffer = get_line(fd, buffer, temp_buffer);
	if (!buffer)
		return (NULL);
	line = extract_split_line(buffer);
	line_len = ft_strlen(line);
	while (buffer[line_len])
		buffer[i++] = buffer[line_len++];
	buffer[i] = '\0';
	return (line);
}
