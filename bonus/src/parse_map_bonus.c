/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 14:58:54 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/16 13:29:14 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d_bonus.h"
#include "cub_macro_bonus.h"
#include "ft_utils_bonus.h"

static int	map_clean_exit(int ret, t_map *map)
{
	int		i;

	i = 0;
	if (map->grid != NULL)
	{
		while (map->grid[i])
		{
			free(map->grid[i]);
			map->grid[i] = NULL;
			i++;
		}
		free(map->grid);
		map->grid = NULL;
	}
	free(map);
	return (ret);
}

static int	map_check_line(t_map *map, char *tmp)
{
	int		x;

	x = 0;
	if (ft_strlen(tmp) == 0)
		return (0);
	while (tmp[x])
	{
		if (ft_isset(tmp[x], MAP_VALID_CHAR))
			x++;
		else
			return (MAP_CHAR_INVALID);
	}
	if (x > map->size_x)
		map->size_x = x;
	return (1);
}

static int	gnl_map_alloc(t_map *map, char *tmp, int y)
{
	if (map->grid == NULL)
	{
		map->size_y = y;
		if (!(map->grid = malloc((map->size_y + 1) * sizeof(char*))))
			return (MAL_ERR_GRID);
		map->grid[y] = NULL;
		free(tmp);
		tmp = NULL;
		return (2);
	}
	else
		return (MAP_ALRD_SET);
}

static int	gnl_map_extract(t_map *map, int fd, char *buff, int y)
{
	int		ret;
	char	*tmp;

	if (y == 0)
	{
		if ((ret = map_check_line(map, buff)) == 1)
			ret = gnl_map_extract(map, fd, buff, y + 1);
		if (map->grid != NULL)
			if ((map->grid[y] = ft_strdup(buff)) == NULL)
				return (MAL_ERR_MAP_DUP);
	}
	else if ((ret = rec_gnl(fd, &tmp)) >= 0)
	{
		if ((ret = map_check_line(map, tmp)) == 1)
			ret = gnl_map_extract(map, fd, buff, y + 1);
		if (map->grid != NULL)
			if ((map->grid[y] = ft_strdup(tmp)) == NULL)
				return (MAL_ERR_MAP_DUP);
		free(tmp);
		tmp = NULL;
	}
	if (ret == 0)
		return (gnl_map_alloc(map, tmp, y));
	return (ret);
}

int			parse_map(t_param *prm)
{
	int			ret;
	t_map		*map;
	t_parse		*tmp;

	if (prm->booleans & MAP_SET)
		return (MAP_ALRD_SET);
	tmp = ((t_parse*)(prm->ptr));
	if (!(map = malloc(sizeof(t_map))))
		return (MAL_ERR_MAP);
	map->grid = NULL;
	map->size_x = 0;
	map->size_y = 0;
	if ((ret = gnl_map_extract(map, tmp->fd, tmp->buff, 0)) < 0)
		return (map_clean_exit(ret, map));
	free(tmp->buff);
	tmp->buff = NULL;
	ft_lstadd_back(&(prm->dlist), ft_lstnew(ID_MAP, map));
	if (get_lst_elem(prm->dlist, ID_MAP) == NULL)
		return (map_clean_exit(MAL_ERR_LIST, map));
	prm->booleans += MAP_SET;
	return (control_map(prm));
}
