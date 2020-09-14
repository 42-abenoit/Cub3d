/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 23:35:36 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/14 16:16:40 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "mlx.h"
#include "cub3d.h"
#include "ft_utils.h"
#include "cub_struct.h"
#include "cub_macro.h"

static int	minimap_clean_exit(int ret, t_minimap *minimap)
{
	if (minimap != NULL)
		free(minimap);
	minimap = NULL;
	return (ret);
}

int			minimap_init(t_param *prm)
{
	t_map		*map;
	t_screen	*screen;
	t_minimap	*minimap;
	
	map = get_lst_elem(prm->dlist, ID_MAP)->content;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	if (!(minimap = malloc(sizeof(t_minimap))))
		return (MAL_ERR_MINIMAP);
	minimap->width = (int)((double)screen->width / 1.5);
	minimap->height = (int)((double)screen->height / 1.5);
	minimap->ratio.x = (double)screen->width / (double)minimap->width;
	minimap->ratio.y = (double)screen->height / (double)minimap->height;
	minimap->map_ratio.x = (double)minimap->width / (double)map->size_x; 
	minimap->map_ratio.y = (double)minimap->height / (double)map->size_y;
	minimap->step = (0.25 / (double)minimap->height);
	ft_lstadd_back(&(prm->dlist), ft_lstnew(ID_MINICONF, minimap));
	if (get_lst_elem(prm->dlist, ID_MINICONF) == NULL)
		return (minimap_clean_exit(MAL_ERR_LIST, minimap));
	return (0);
}

void	minimap_to_screen(int x, t_ray *ray, t_param *prm)
{
	int			y;
	int			offset_x;
	double		persp;
	t_int_coord	mini;
	t_int_coord	start;
	t_screen	*screen;
	t_minimap	*minimap;
	t_map		*map;
	t_player	*player;

	map	= get_lst_elem(prm->dlist, ID_MAP)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	minimap = get_lst_elem(prm->dlist, ID_MINICONF)->content;
	start.x = (screen->width / minimap->ratio.x) / 4;
	start.y = (screen->height / minimap->ratio.y) / 3;
	y = start.y;
	if (x < start.x || x > start.x + minimap->width - 1)
		return ;
	persp = 0.75;
	while (y < start.y + minimap->height - 1)
	{
		mini.y = (int)floor((double)(y - start.y) / minimap->map_ratio.y);
		offset_x = ((double)minimap->width / 2.0) * (1.0 - persp);
		if (x >= start.x + offset_x && x <= start.x + minimap->width - offset_x)
		{
			if (x < screen->width)
				mini.x = (int)floor((double)((int)(double)((x - start.x) - offset_x)
										/ persp)
										/ minimap->map_ratio.x);
			else
				mini.x = (int)floor((double)((int)(double)((x - start.x - minimap->width - offset_x)
										* persp))
										/ minimap->map_ratio.x);
			if ((mini.y >= 0 && mini.y < map->size_y) && (mini.x >= 0 && mini.x < ft_strlen(map->grid[mini.y])))
			{
				if (map->grid[mini.y][mini.x] == '1')
					ray->color = 0x00909090;
				else if (map->grid[mini.y][mini.x] == '2')
					ray->color = 0x00FAFFFA;
				else if (mini.y == floor(player->pos.y) && mini.x == floor(player->pos.x))
					ray->color = 0x0000FFFF;
				else
					ray->color = 0x00F0DEB1;
			}
			if ((ray->color & 0x00FFFFFF) != 0)
				ray->line_buff[y] = ray->color;
		}
		y++;
		persp += minimap->step;
	}
}
