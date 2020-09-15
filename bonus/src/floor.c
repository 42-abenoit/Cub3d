/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 15:36:12 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/15 13:35:26 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include "cub_macro.h"
#include "cub_struct.h"
#include "ft_utils.h"

void		floor_init(t_floor *floor, t_ray *ray)
{
	if (ray->id_side % 2 == 0 && ray->dir.x >= 0)
	{
		floor->wall.x = ray->map.x;
		floor->wall.y = ray->map.y + ray->wall_x;
	}
	else if (ray->id_side % 2 == 0 && ray->dir.x < 0)
	{
		floor->wall.x = ray->map.x + 1.0;
		floor->wall.y = ray->map.y + ray->wall_x;
	}
	else if (ray->id_side % 2 == 1 && ray->dir.y >= 0)
	{
		floor->wall.x = ray->map.x + ray->wall_x;
		floor->wall.y = ray->map.y;
	}
	else
	{
		floor->wall.x = ray->map.x + ray->wall_x;
		floor->wall.y = ray->map.y + 1.0;
	}
	floor->dist_wall = ray->perp_wall_dist;
	floor->dist_player = 0.0;
}

static void	floor_set_vars(int y, t_floor *floor, t_param *prm)
{
	t_screen	*screen;
	t_player	*player;

	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	floor->current_dist = (screen->height + (2.0 * player->pos_z))
						/ (2.0 * (y - player->pitch) - screen->height);
	floor->weight = (floor->current_dist - floor->dist_player)
					/ (floor->dist_wall - floor->dist_player);
	floor->current.x = floor->weight * floor->wall.x
							+ (1.0 - floor->weight) * player->pos.x;
	floor->current.y = floor->weight * floor->wall.y
							+ (1.0 - floor->weight) * player->pos.y;
	floor->tex.x = (int)((floor->current.x - 1)
					* floor->tx_ptr->width) & (floor->tx_ptr->width - 1);
	floor->tex.y = (int)((floor->current.y - 1)
					* floor->tx_ptr->height) & (floor->tx_ptr->height - 1);
}

void		ray_fill_line_floor(int x, t_floor *floor, t_ray *ray, t_param *prm)
{
	int			y;
	double		floor_dist;
	t_screen	*screen;
	t_player	*player;
	t_render	*render;

	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	render = prm->ptr;
	floor->tx_ptr = get_lst_elem(prm->dlist, ID_TX_F)->content;
	y = ray->horizon;
	while (y < screen->height)
	{
		floor_set_vars(y, floor, prm);
		floor_dist = (player->pos.x - floor->current.x)
					* (player->pos.x - floor->current.x)
					+ (player->pos.y - floor->current.y)
					* (player->pos.y - floor->current.y);
		ray->color = get_pixel_color(floor->tex.x,
								floor->tex.y, &floor->tx_ptr->data);
		ray->color = apply_fog(floor_dist, ray->color, prm);
		if ((ray->color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(&render->img, x, y, ray->color);
		y++;
	}
}
