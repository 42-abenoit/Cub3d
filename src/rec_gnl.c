/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_gnl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <abenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 18:00:38 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/25 17:32:29 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

static int		line_init(char **line, int offset, int ret)
{
	if (!(*line = malloc((offset + 1) * sizeof(char))))
		return (-1);
	((*line)[offset]) = '\0';
	return (ret);
}

static int		recursive_get_line(char **line, int fd, int offset)
{
	char	buffer;
	int		ret;

	ret = read(fd, &buffer, 1);
	if (ret == 1)
	{
		if (buffer == '\n' || buffer == '\0')
			return (line_init(line, offset, 1));
		else
		{
			ret = recursive_get_line(line, fd, offset + 1);
			if ((*line) != NULL)
				((*line)[offset]) = buffer;
			return (ret);
		}
	}
	else if (ret == 0)
		return (line_init(line, offset, 0));
	return (-1);
}

int				rec_gnl(int fd, char **line)
{
	char	buffer;

	if (fd < 0 || !line || read(fd, &buffer, 0) < 0)
		return (-1);
	*line = NULL;
	return (recursive_get_line(line, fd, 0));
}
