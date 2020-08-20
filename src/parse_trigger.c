/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_trigger.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 20:43:25 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/20 16:21:36 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "cub3d.h"
#include "cub_macro.h"
#include "ft_utils.h"

static int	parse_map(t_param *prm)
{
	t_parse		*tmp;

	tmp = ((t_parse*)(prm->ptr));
	printf("bool = %x\n", prm->booleans);
	printf("buff = %s\n", tmp->buff);
	ft_exit(0, prm);
	return (0);
}

static int	open_path(t_parse *tmp)
{
	tmp->fd = open(tmp->buff, O_RDONLY);
	free(tmp->buff);
	tmp->buff = 0;
	if (read(tmp->fd, &tmp->buff, 0) < 0)
		return (0);
	return (1);
}

int			parse_trigger(t_param *prm)
{
	t_parse		*tmp;
	int			ret;

	tmp = ((t_parse*)(prm->ptr));
	if (!(tmp->id_strings = ft_split(ID_STRINGS, "/")))
		return (ft_exit(ID_SPLIT_ERR, prm));
	if (!open_path(tmp))
		return (ft_exit(WRONG_FILE_PATH, prm));
	while (rec_gnl(tmp->fd, &tmp->buff) == 1)
	{
		if (ft_isset(tmp->buff[0], IS_ID))
		{
			if ((ret = parse_line(prm)) < 0)
				return (ft_exit(ret, prm));
		}
		else if (ft_isset(tmp->buff[0], VALID_MAP)
					|| ft_isset(tmp->buff[0], WHITESPACES))
			return (parse_map(prm));
		else if (ft_strlen(tmp->buff) > 0)
			return (ft_exit(NOT_ID_CHAR, prm));
		free(tmp->buff);
	}
	return (ft_exit(NO_MAP_FOUND, prm));
}
