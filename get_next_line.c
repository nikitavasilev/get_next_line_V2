/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 02:58:22 by nvasilev          #+#    #+#             */
/*   Updated: 2021/08/18 16:23:56 by nvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_and_reset(char **pointer)
{
	free(*pointer);
	*pointer = NULL;
}

char	*get_line(char **remainder, char **line)
{
	size_t	len;
	char	*new_rem;

	len = 0;
	new_rem = NULL;
	while ((*remainder)[len] != '\n' && (*remainder)[len])
		len++;
	if ((*remainder)[len] == '\n')
	{
		*line = ft_substr(*remainder, 0, (len + 1));
		new_rem = ft_strdup(&(*remainder)[len + 1]);
	}
	else
		*line = ft_strdup(*remainder);
	free_and_reset(remainder);
	return (new_rem);
}

size_t	read_file(int fd, char **buffer, char **remainder, char **line)
{
	char	*temp;
	size_t	ret_read;

	ret_read = TRUE;
	while (!ft_strchr(*remainder, '\n') && ret_read)
	{
		ret_read = read(fd, *buffer, BUFFER_SIZE);
		(*buffer)[ret_read] = '\0';
		temp = *remainder;
		*remainder = ft_strjoin(temp, *buffer);
		free(temp);
	}
	free_and_reset(buffer);
	*remainder = get_line(remainder, line);
	if (!(**line))
		free_and_reset(line);
	return (ret_read);
}

char	*get_next_line(int fd)
{
	static char		*remainder = NULL;
	char			*buffer;
	char			*line;
	size_t			ret_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (read(fd, buffer, 0) < 0)
	{
		free(buffer);
		return (NULL);
	}
	if (!remainder)
		remainder = ft_strdup("");
	ret_read = read_file(fd, &buffer, &remainder, &line);
	if (!ret_read && !line)
		return (NULL);
	return (line);
}
