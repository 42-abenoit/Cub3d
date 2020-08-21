/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 14:58:54 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/21 16:55:28 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"
#include "cub_macro.h"
#include "ft_utils.h"

static int	map_clean_exit(int ret, t_map *map)
{
	free(map);
	return (ret);
}

static int	gnl_map_extract(t_map *map, int fd, char *buff, int size_y)
{
	fd = 0;
	size_y = 1;
	(void)buff;
	return (map_clean_exit(0, map));
}

int			parse_map(t_param *prm)
{
	t_map		*map;
	t_parse		*tmp;

	tmp = ((t_parse*)(prm->ptr));
	if (!(map = malloc(sizeof(t_map))))
		return (MAL_ERR_MAP);
	printf("bool = %x\n", prm->booleans);
	printf("buff = %s\n", tmp->buff);
	return (gnl_map_extract(map, tmp->fd, tmp->buff, 0));
	ft_exit(0, prm);
	return (0);
}
