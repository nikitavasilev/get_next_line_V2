/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 02:58:22 by nvasilev          #+#    #+#             */
/*   Updated: 2021/08/18 19:14:13 by nvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
*	FREE_AND_RESET
*	--------------
*	DESCRIPTION
*	We use this function to free and set to null a pointer.
*	PARAMETERS
*	#1. The pointer to be cleared
*/

void	free_and_reset(char **pointer)
{
	free(*pointer);
	*pointer = NULL;
}

/*
*	GET_LINE
*	--------
*	DESCRIPTION
*	This function extracts the line from the static variable "remainder".
*	A line either ends with '\n' or EOF ('\0'). We extract the caracters
*	before and stock them in "line". We also update the "remainder".
*	PARAMETERS
*	#1. The static buffer "remainder" (stock of previous GNL calls)
*	#2. The pointer to the future line (that we will extract from #1)
*	RETURN VALUES
*	We return the updated "remainder":
*	(original value - line extracted) -> updated remainder
*/

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

/*
*	READ_FILE
*	---------
*	DESCRIPTION
*	This function checks if there is a line break in the "remainder" variable.
*	If there is, we send the "remainder" to GET_LINE to extract the line.
*	If not, we read the file in the loop until we reach the next '\n' or EOF.
*	PARAMETERS
*	#1. A file descriptor
*	#2. A buffer of the size of BUFFER_SIZE + 1 that will be used by READ(2)
*	#3. The remainder of previous calls of GNL (used )
*	#4. The pointer to the line to be extracted from buffer
*	RETURN VALUES
*	Same return values as READ(2):
*	- number of bytes read
*	- 0 if EOF or -1 if an error occurs
*/

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

/*
*	GET_NEXT_LINE
*	-------------
*	DESCRIPTION
*	This function takes an opened file descriptor and returns its next line.
*	This function has undefined behavior when reading from a binary file.
*	PARAMETERS
*	#1. A file descriptor
*	RETURN VALUES
*	If successful, get_next_line returns a string with the full line ending in
*	a line break ('\n') when there is one.
*	If an error occurs, or there's nothing more to read, it returns NULL.
*/

char	*get_next_line(int fd)
{
	static char		*remainder = NULL;
	char			*buffer;
	char			*line;
	size_t			ret_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
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
