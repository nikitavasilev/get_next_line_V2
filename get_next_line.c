/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 02:58:22 by nvasilev          #+#    #+#             */
/*   Updated: 2021/08/16 00:48:52 by nvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <strings.h>
#include <string.h>

char	*get_next_line(int fd)
{
	char			buf[BUFFER_SIZE + 1];
	char			*line;
	int				i;
	static char		*rem;
	char			*tmp;

	tmp = NULL;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buf, 0) < 0)
		return (NULL);
	bzero(buf, BUFFER_SIZE + 1);
	printf ("CHARACTERS READ: %lu\n", read(fd, buf, BUFFER_SIZE));
	printf("%s\n\n", buf);

	i = 0;
	while (buf[i] != '\n' && buf[i] != EOF)
	{
		i++;
	}
	if (rem)
	{
		tmp = line;
		line = ft_strjoin(rem, buf);
		free(tmp);
	}
	else
	{
		if (!(line = malloc(strlen(buf) + 1 - i)))
			return (0);
		strncpy(line, buf, i++);
	}
	printf("LINE: %s\n", line);
	//strncpy(rem, &buf[i] + 1, strlen(buf) + 1 - i);
	tmp = rem;
	rem = ft_strdup(&buf[i] + 1);
	free(tmp);
	printf("REMAINDER: %s\n", rem);
	return (line);
}
