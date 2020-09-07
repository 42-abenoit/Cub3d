/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:06:48 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/06 20:21:14 by abenoit          ###   ########.fr       */
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
	double		pos_y;
	t_player	*player;

	sky = get_lst_elem(prm->dlist, ID_TX_SK)->content;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
//	printf("x = %f\n", prm->dir.x);
//	printf("y = %f\n", prm->dir.y);
	y = 0;
//	Rx = ((double)prm->res_x) / ((double)bonus->sky_tex.tex_width);
	Rx = ((double)sky->width / 4.0) / ((double)screen->width);
	plop = (atan2(ray->dir.y, ray->dir.x) / CIRCLE) / 2;
//	plop = (atan2(prm->dir.y, prm->dir.x) / CIRCLE) / 2.0;
	if (plop < 0)
		plop = 1.0 + plop;
//	Ry = ((double)prm->res_y) / (double)bonus->sky_tex.tex_height;
	Ry = ((double)sky->height / 2.0) / ((double)screen->height);
	sky_x = (int)(fabs((x * Rx) + (plop * sky->width * 4.0)));

//	printf("x = %f\n", Rx);
//	printf("y = %f\n", Ry);
	while (y < ray->wall_mid)
	{
		pos_y = (y + (player->pitch + player->pos_z));
//		pos_y = (y - screen->height + player->pitch);
		if (pos_y > 0)
		{
			sky_y = (int)fabs(pos_y * Ry);
			ray->color = get_pixel_color(sky_x, sky_y, &sky->data);
			ray->line_buff[y] = ray->color;
		}
		y++;
	}
}
