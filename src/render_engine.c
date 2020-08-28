/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_engine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 16:16:35 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/28 11:24:19 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "cub3d.h"
#include "ft_utils.h"
#include "cub_macro.h"
#include "cub_struct.h"

static void		ray_init(int x, t_ray *ray, t_param *prm)
{
	t_screen	*screen;
	t_player	*player;

	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	ray->camera_x = 2 * x / (double)screen->width - 1;
	ray->dir.x = player->dir.x + atan(player->dir.x) * ray->camera_x;
	ray->dir.y = player->dir.y + atan(player->dir.y) * ray->camera_x;
	ray->map.x = (int)player->pos.x;
	ray->map.y = (int)player->pos.y;
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
	ray->hit = 0;
}

static void		img_refresh(t_ray *ray, t_param *prm)
{
	t_render	*render;

	render = prm->ptr;
	if (prm->booleans & IMG_SET)
	{
		mlx_destroy_image(render->mlx, render->current.img);
		render->current.addr = NULL;
	}
	else
		prm->booleans += IMG_SET;
	free(ray->line_buff);
	render->current = ray->img;
	mlx_put_image_to_window(render->mlx, render->win,
							render->current.img, 0, 0);
}

void			fill_line(int x, t_ray *ray, t_param *prm)
{
	int			y;
	t_screen	*screen;

	y = 0;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	while (y < screen->height)
	{
		my_mlx_pixel_put(&ray->img, x, y, 0x00FFFF00);
		y++;
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
	while (x < screen->width)
	{
		ray_init(x, &ray, prm);
		fill_line(x, &ray, prm);
		x++;
	}
	img_refresh(&ray, prm);
	return (0);
}
