/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_engine_img_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:21:53 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/22 19:18:53 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "cub3d_bonus.h"
#include "ft_utils_bonus.h"
#include "cub_macro_bonus.h"
#include "cub_struct_bonus.h"

void			img_refresh(t_param *prm)
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
	render->current = render->img;
	mlx_put_image_to_window(render->mlx, render->win,
							render->current.img, 0, 0);
}

void			fill_buffer(t_ray *ray, t_param *prm)
{
	int			y;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		ray->tex.y = (int)ray->tex_pos;
		if (ray->tex.y < 0)
			ray->tex.y = 0;
		if (ray->tex.y >= ray->tx->height)
			ray->tex.y = ray->tx->height - 1;
		ray->tex_pos += ray->tex_step;
		ray->color = get_pixel_color(ray->tex.x, ray->tex.y,
									&ray->tx->data);
		ray->color = apply_fog(ray->dist, ray->color, prm);
		if ((ray->color & 0x00FFFFFF) != 0)
			ray->line_buff[y] = ray->color;
		y++;
	}
}

void			fill_line(int x, t_ray *ray, t_param *prm)
{
	int			y;
	t_render	*render;
	t_screen	*screen;

	y = 0;
	render = prm->ptr;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	while (y < screen->height)
	{
		my_mlx_pixel_put(&render->img, x, y, ray->line_buff[y]);
		y++;
	}
}
