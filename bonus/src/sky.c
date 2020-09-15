/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:06:48 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/15 11:47:25 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include "ft_utils.h"
#include "cub_macro.h"
#include "cub_struct.h"

void	fill_sky_line(int x, t_ray *ray, t_param *prm)
{
	t_coord			ratio;
	t_int_coord		sky_coord;
	int				y;
	double			plop;
	t_tx			*sky;
	t_screen		*screen;
	t_render		*render;
	int				offset_y;

	render = prm->ptr;
	sky = get_lst_elem(prm->dlist, ID_TX_SK)->content;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	y = 0;
	ratio.x = ((double)sky->width / 8.0) / ((double)screen->width);
	plop = (atan2(ray->dir.y, ray->dir.x) / M_PI) / 2;
	if (plop < 0)
		plop = 1.0 + plop;
	ratio.y = ((double)sky->height / 2.0) / ((double)screen->height);
	sky_coord.x = (int)(floor((x * ratio.x) + (plop * sky->width)));
	while (y < ray->horizon)
	{
		offset_y = ((screen->height * 2.0) - (ray->horizon - y));
		sky_coord.y = (int)floor((double)offset_y * ratio.y);
		if (sky_coord.y > 0 && sky_coord.y < sky->height - 1)
		{
			ray->color = get_pixel_color(sky_coord.x, sky_coord.y, &sky->data);
			if ((ray->color & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(&render->img, x, y, ray->color);
		}
		y++;
	}
}
