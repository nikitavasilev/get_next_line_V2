/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 03:12:14 by nvasilev          #+#    #+#             */
/*   Updated: 2021/08/15 12:10:08 by nvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		main(void)
{
	int		fd;
	size_t	i;
	char	*line;

	line = NULL;
	fd = open("file.txt", O_RDONLY);
	//get_next_line(fd);
	//get_next_line(fd);
	//get_next_line(fd);

	i = 0;
	while ((line = get_next_line(fd)))
	{
		printf("\nCALL #%lu\n", i++);
		printf("\nLINE: %s\n", line);
		free(line);
	}

	//printf("%s\n", get_next_line(fd));
	close(fd);
	return (0);
}
