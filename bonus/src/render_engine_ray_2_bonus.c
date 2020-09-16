/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_engine_ray_2_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:17:33 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/16 13:35:46 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "cub3d_bonus.h"
#include "ft_utils_bonus.h"
#include "cub_macro_bonus.h"
#include "cub_struct_bonus.h"

static void		ray_increment(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x;
		ray->map.x += ray->step.x;
		ray->id_side = ray->side.x;
	}
	else
	{
		ray->side_dist.y += ray->delta_dist.y;
		ray->map.y += ray->step.y;
		ray->id_side = ray->side.y;
	}
}

void			ray_hit_scan(t_ray *ray, t_param *prm)
{
	t_map		*map;
	t_player	*player;
	t_conf		*conf;

	map = get_lst_elem(prm->dlist, ID_MAP)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	while (ray->hit == 0 && ray->dist < conf->view_depth)
	{
		ray_increment(ray);
		if (map->grid[ray->map.y][ray->map.x] == '1')
			ray->hit = 1;
		ray->dist = (player->pos.x - ray->map.x)
					* (player->pos.x - ray->map.x)
					+ (player->pos.y - ray->map.y)
					* (player->pos.y - ray->map.y);
	}
}

void			ray_perspective(t_ray *ray, t_param *prm)
{
	t_player	*player;
	t_screen	*screen;

	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	if (ray->id_side % 2 == 0)
		ray->perp_wall_dist = (ray->map.x - player->pos.x
								+ (1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->perp_wall_dist = (ray->map.y - player->pos.y
								+ (1 - ray->step.y) / 2) / ray->dir.y;
	ray->line_height = (int)(screen->height / ray->perp_wall_dist);
	ray->draw_start = (-ray->line_height / 2) + (screen->height / 2)
					+ player->pitch + (player->pos_z
										/ ray->perp_wall_dist);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2) + (screen->height / 2)
					+ player->pitch + (player->pos_z
										/ ray->perp_wall_dist);
	if (ray->draw_end >= screen->height)
		ray->draw_end = screen->height - 1;
	ray->horizon = (screen->height / 2.0) + player->pitch;
}

static void		side_texture(t_ray *ray, t_param *prm)
{
	if (ray->id_side == 0)
		ray->tx_ptr = get_lst_elem(prm->dlist, ID_TX_WE)->content;
	else if (ray->id_side == 1)
		ray->tx_ptr = get_lst_elem(prm->dlist, ID_TX_NO)->content;
	else if (ray->id_side == 2)
		ray->tx_ptr = get_lst_elem(prm->dlist, ID_TX_EA)->content;
	else if (ray->id_side == 3)
		ray->tx_ptr = get_lst_elem(prm->dlist, ID_TX_SO)->content;
}

void			ray_texture(t_ray *ray, t_param *prm)
{
	t_player	*player;
	t_screen	*screen;

	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	side_texture(ray, prm);
	if (ray->id_side % 2 == 0)
		ray->wall_x = player->pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		ray->wall_x = player->pos.x + ray->perp_wall_dist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex.x = (int)(ray->wall_x * ray->tx_ptr->width);
	if ((ray->id_side % 2 == 0) && ray->dir.x > 0)
		ray->tex.x = ray->tx_ptr->width - ray->tex.x - 1;
	if (ray->id_side % 2 == 1 && ray->dir.y < 0)
		ray->tex.x = ray->tx_ptr->width - ray->tex.x - 1;
	ray->tex_step = 1.0 * ray->tx_ptr->height / ray->line_height;
	ray->tex_pos = (ray->draw_start - player->pitch
					- (player->pos_z / ray->perp_wall_dist)
					- screen->height / 2 + ray->line_height / 2)
					* ray->tex_step;
}
