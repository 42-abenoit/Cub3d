/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 23:35:36 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/16 12:46:39 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "mlx.h"
#include "cub3d.h"
#include "ft_utils.h"
#include "cub_struct.h"
#include "cub_macro.h"

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
	minimap->start.x = (screen->width / minimap->ratio.x) / 4;
	minimap->start.y = (screen->height / minimap->ratio.y) / 3;
	ft_lstadd_back(&(prm->dlist), ft_lstnew(ID_MINIMAP, minimap));
	if (get_lst_elem(prm->dlist, ID_MINIMAP) == NULL)
	{
		free(minimap);
		minimap = NULL;
		return (MAL_ERR_LIST);
	}
	return (0);
}

static void	get_minimap_color(int x, int y, t_int_coord mini, t_param *prm)
{
	int			color;
	t_map		*map;
	t_player	*player;
	t_render	*render;

	render = prm->ptr;
	map = get_lst_elem(prm->dlist, ID_MAP)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	color = 0;
	if ((mini.y >= 0 && mini.y < map->size_y)
		&& (mini.x >= 0 && mini.x < ft_strlen(map->grid[mini.y])))
	{
		if (map->grid[mini.y][mini.x] == '1')
			color = 0x00909090;
		else if (map->grid[mini.y][mini.x] == '2')
			color = 0x00FAFFFA;
		else if (mini.y == floor(player->pos.y)
				&& mini.x == floor(player->pos.x))
			color = 0x0000FFFF;
	}
	if ((color & 0x00FFFFFF) != 0)
		my_mlx_pixel_put(&render->img, x, y, color);
}

static int	resize_x_axis(int x, int offset_x, double persp, t_minimap *minimap)
{
	int			mini_x;

	mini_x = (((x - minimap->start.x)
				- offset_x) / persp)
				/ minimap->map_ratio.x;
	return (mini_x);
}

void		minimap_to_screen(int x, t_param *prm)
{
	int			y;
	int			offset_x;
	double		persp;
	t_int_coord	mini;
	t_minimap	*minimap;

	minimap = get_lst_elem(prm->dlist, ID_MINIMAP)->content;
	y = minimap->start.y;
	if (x <= minimap->start.x || x >= minimap->start.x + minimap->width)
		return ;
	persp = 0.75;
	while (y < minimap->start.y + minimap->height)
	{
		mini.y = (double)(y - minimap->start.y) / minimap->map_ratio.y;
		offset_x = ((double)minimap->width / 2.0) * (1.0 - persp);
		if (x > minimap->start.x + offset_x
			&& x < minimap->start.x + minimap->width - offset_x)
		{
			mini.x = resize_x_axis(x, offset_x, persp, minimap);
			get_minimap_color(x, y, mini, prm);
		}
		y++;
		persp += minimap->step;
	}
}
