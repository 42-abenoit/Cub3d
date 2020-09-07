/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_engine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 16:16:35 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/07 16:23:14 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "cub3d.h"
#include "ft_utils.h"
#include "cub_macro.h"
#include "cub_struct.h"

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
	ray->sprites = NULL;
	set_step_x(ray, prm);
	set_step_y(ray, prm);
}

static void		cast_x_rays(int x, int x_max, t_ray *ray, t_param *prm)
{
	while (x < x_max)
	{
		ray_init(x, ray, prm);
		ray_hit_scan(ray, prm);
		ray_perspective(ray, prm);
		ray_texture(ray, prm);
		fill_buffer(ray, prm);
		sprite_projection(ray, prm);
		ray_fill_line_sprite(x, ray, prm);
		fill_line(x, ray, prm);
		ft_clear_list(&ray->sprites);
		x++;
	}
}

int				ray_caster(t_param *prm)
{
	t_ray		ray;
	t_screen	*screen;
	t_render	*render;
	int			x;

	x = 0;
	render = prm->ptr;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	ray.img = my_mlx_new_image(render->mlx, screen->width, screen->height);
	if (!(ray.line_buff = malloc(screen->height * sizeof(int))))
		return (MAL_ERR_BUFF);
	cast_x_rays(x, screen->width - 1, &ray, prm);
	img_refresh(&ray, prm);
	ft_move(prm);
	return (0);
}
