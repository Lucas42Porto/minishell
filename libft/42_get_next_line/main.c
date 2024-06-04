/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:18:08 by lumarque          #+#    #+#             */
/*   Updated: 2023/11/20 16:48:09 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	int		fd;
	int		fd1;
	char	*line;
	char	*line1;

	fd = open("text.txt", O_RDONLY);
	fd1 = open("music.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line1 = get_next_line(fd1);
	printf("%s", line1);
	line1 = get_next_line(fd1);
	printf("%s", line1);
	line = get_next_line(fd);
	printf("%s", line);
	close(fd);
	close(fd1);
	return (0);
}
