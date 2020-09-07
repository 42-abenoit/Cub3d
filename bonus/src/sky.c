/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:06:48 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/07 16:10:32 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include "ft_utils.h"
#include "cub_macro.h"
#include "cub_struct.h"

void	fill_sky_line(int x, t_ray *ray, t_param *prm)
{
	int		sky_x;
	int		sky_y;
	double	Rx;
	double	Ry;
	int		y;
	double	plop;
	double	CIRCLE = 3.14159265359;
	t_tx	*sky;
	t_screen	*screen;
	int			pos_y;

	sky = get_lst_elem(prm->dlist, ID_TX_SK)->content;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	y = 0;
	Rx = ((double)sky->width / 8.0) / ((double)screen->width);
	plop = (atan2(ray->dir.y, ray->dir.x) / CIRCLE) / 2;
	if (plop < 0)
		plop = 1.0 + plop;
	Ry = ((double)sky->height / 2.0) / ((double)screen->height);
	sky_x = (int)(floor((x * Rx) + (plop * sky->width)));
	while (y < ray->horizon)
	{
		pos_y = ((screen->height * 2.0) - (ray->horizon - y)); 
		sky_y = (int)floor((double)pos_y * Ry);
		if (sky_y > 0 && sky_y < sky->height - 1)
		{
			ray->color = get_pixel_color(sky_x, sky_y, &sky->data);
			if ((ray->color & 0x00FFFFFF) != 0)
				ray->line_buff[y] = ray->color;
		}
		y++;
	}
}
