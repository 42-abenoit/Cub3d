/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_engine_img.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:21:53 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/16 17:55:45 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "cub3d.h"
#include "ft_utils.h"
#include "cub_macro.h"
#include "cub_struct.h"

void			img_refresh(t_ray *ray, t_param *prm)
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

void			fill_buffer(t_ray *ray, t_param *prm)
{
	int			y;
	t_hcc		*hcc;
	t_screen	*screen;

	y = -1;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	hcc = get_lst_elem(prm->dlist, ID_HCC_C)->content;
	while (++y < ray->draw_start)
		ray->line_buff[y] = hcc->hcc;
	y -= 1;
	while (++y <= ray->draw_end)
	{
		ray->tex.y = (int)ray->tex_pos & (ray->tx_ptr->height - 1);
		ray->tex_pos += ray->tex_step;
		ray->color = get_pixel_color(ray->tex.x, ray->tex.y,
									&ray->tx_ptr->data);
		ray->line_buff[y] = ray->color;
	}
	hcc = get_lst_elem(prm->dlist, ID_HCC_F)->content;
	y -= 1;
	while (++y < screen->height)
		ray->line_buff[y] = hcc->hcc;
}

void			fill_line(int x, t_ray *ray, t_param *prm)
{
	int			y;
	t_screen	*screen;

	y = 0;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	while (y < screen->height)
	{
		my_mlx_pixel_put(&ray->img, x, y, ray->line_buff[y]);
		y++;
	}
}
