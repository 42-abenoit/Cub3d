/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:06:48 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/15 13:45:13 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include "ft_utils.h"
#include "cub_macro.h"
#include "cub_struct.h"

void	fill_sky_line(int x, t_ray *ray, t_param *prm)
{
	int				y;
	t_sky			sky;
	t_tx			*tx;
	t_screen		*screen;
	t_render		*render;

	render = prm->ptr;
	tx = get_lst_elem(prm->dlist, ID_TX_SK)->content;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	y = 0;
	sky.ratio.x = ((double)tx->width / 8.0) / ((double)screen->width);
	sky.orientation = (atan2(ray->dir.y, ray->dir.x) / M_PI) / 2;
	if (sky.orientation < 0)
		sky.orientation = 1.0 + sky.orientation;
	sky.ratio.y = ((double)tx->height / 2.0) / ((double)screen->height);
	sky.coord.x = (x * sky.ratio.x)
					+ (sky.orientation * (tx->width - 1));
	while (y <= ray->horizon)
	{
		sky.offset_y = (((screen->height - 1) * 2.0) - (ray->horizon - y));
		sky.coord.y = (double)sky.offset_y * sky.ratio.y;
		if (sky.coord.y >= 0 && sky.coord.y <= tx->height - 1)
		{
			ray->color = get_pixel_color(sky.coord.x, sky.coord.y, &tx->data);
			if ((ray->color & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(&render->img, x, y, ray->color);
		}
		y++;
	}
}
