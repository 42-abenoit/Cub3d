/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_engine_ray_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 16:10:04 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/16 13:35:55 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mlx.h"
#include "cub3d_bonus.h"
#include "ft_utils_bonus.h"
#include "cub_macro_bonus.h"
#include "cub_struct_bonus.h"

static void		set_step_x(t_ray *ray, t_param *prm)
{
	t_player	*player;

	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (player->pos.x - ray->map.x) * ray->delta_dist.x;
		ray->side.x = 0;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0
							- player->pos.x) * ray->delta_dist.x;
		ray->side.x = 2;
	}
}

static void		set_step_y(t_ray *ray, t_param *prm)
{
	t_player	*player;

	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (player->pos.y - ray->map.y) * ray->delta_dist.y;
		ray->side.y = 1;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - player->pos.y)
							* ray->delta_dist.y;
		ray->side.y = 3;
	}
}

void			ray_init(int x, t_ray *ray, t_param *prm)
{
	t_screen	*screen;
	t_player	*player;

	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	ray->camera_x = 2 * x / (double)screen->width - 1;
	ray->dir.x = player->dir.x + player->plane.x * ray->camera_x;
	ray->dir.y = player->dir.y + player->plane.y * ray->camera_x;
	ray->map.x = (int)player->pos.x;
	ray->map.y = (int)player->pos.y;
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
	ray->hit = 0;
	ray->dist = 0;
	set_step_x(ray, prm);
	set_step_y(ray, prm);
}
