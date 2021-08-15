/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 03:12:14 by nvasilev          #+#    #+#             */
/*   Updated: 2021/08/16 00:59:18 by nvasilev         ###   ########.fr       */
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

	i = 1;
	while ((line = get_next_line(fd)))
	{
		printf("\nLINE #%lu: %s\n", i++, line);
		free(line);
	}
	close(fd);
	return (0);
}
