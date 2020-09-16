/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_engine_img_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:21:53 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/16 13:35:39 by abenoit          ###   ########.fr       */
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

void			fill_buffer(int x, t_ray *ray, t_param *prm)
{
	int			y;
	t_render	*render;

	y = ray->draw_start;
	render = prm->ptr;
	while (y < ray->draw_end)
	{
		ray->tex.y = (int)ray->tex_pos & (ray->tx_ptr->height - 1);
		ray->tex_pos += ray->tex_step;
		ray->color = get_pixel_color(ray->tex.x, ray->tex.y,
									&ray->tx_ptr->data);
		ray->color = apply_fog(ray->dist, ray->color, prm);
		if ((ray->color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(&render->img, x, y, ray->color);
		y++;
	}
}
