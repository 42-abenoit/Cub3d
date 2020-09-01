/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:06:45 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/27 12:38:10 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"
#include "ft_utils.h"
#include "cub_struct.h"
#include "cub_macro.h"

static int	ctrl_clean_exit(int ret, char **vgrid)
{
	int		i;

	i = 0;
	if (vgrid != NULL)
	{
		while (vgrid[i])
		{
			free(vgrid[i]);
			vgrid[i] = NULL;
			i++;
		}
		free(vgrid);
		vgrid = NULL;
	}
	return (ret);
}

static int	vgrid_init(char ***vgrid, int size_x, int size_y)
{
	int		y;
	int		x;

	y = 0;
	if (!(*vgrid = malloc((size_y + 1) * sizeof(char*))))
		return (MAL_ERR_GRID);
	while (y < size_y)
	{
		if (!((*vgrid)[y] = malloc((size_x + 1) * sizeof(char))))
			return (MAL_ERR_GRID);
		x = 0;
		while (x < size_x)
		{
			(*vgrid)[y][x] = '0';
			x++;
		}
		(*vgrid)[y][x] = '\0';
		y++;
	}
	(*vgrid)[y] = NULL;
	return (0);
}

static int	flood_fill(int x, int y, char **grid, char **vgrid)
{
	if ((y < 0 || grid[y] == NULL) || (x < 0 || x > ft_strlen(grid[y])))
		return (-1);
	if (vgrid[y][x] == '1')
		return (1);
	else if (ft_isset(grid[y][x], MAP_PLAY_AREA))
	{
		vgrid[y][x] = '1';
		if ((flood_fill(x + 1, y, grid, vgrid) == 1)
				&& (flood_fill(x - 1, y - 1, grid, vgrid) == 1)
				&& (flood_fill(x - 1, y + 1, grid, vgrid) == 1)
				&& (flood_fill(x + 1, y + 1, grid, vgrid) == 1)
				&& (flood_fill(x + 1, y - 1, grid, vgrid) == 1)
				&& (flood_fill(x - 1, y, grid, vgrid) == 1)
				&& (flood_fill(x, y + 1, grid, vgrid) == 1)
				&& (flood_fill(x, y - 1, grid, vgrid) == 1))
			return (1);
		else
			return (-1);
	}
	else if (grid[y][x] == '1')
		return (1);
	else
		return (-1);
}

int			control_map(t_param *prm)
{
	int		x;
	int		y;
	int		ret;
	t_map	*map;
	char	**vgrid;

	vgrid = NULL;
	map = (t_map*)(get_lst_elem(prm->dlist, ID_MAP)->content);
	if ((ret = vgrid_init(&vgrid, map->size_x, map->size_y)) < 0)
		return (ctrl_clean_exit(ret, vgrid));
	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (vgrid[y][x] != '1' && ft_isset(map->grid[y][x], MAP_PLAY_AREA))
				if ((ret = flood_fill(x, y, map->grid, vgrid) != 1))
					return (ctrl_clean_exit(MAP_LEAKS, vgrid));
			x++;
		}
		y++;
	}
	return (ctrl_clean_exit(0, vgrid));
}
