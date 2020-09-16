/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_save_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 15:42:35 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/16 16:36:28 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mlx.h"
#include "cub3d_bonus.h"
#include "ft_utils_bonus.h"
#include "cub_macro_bonus.h"
#include "cub_struct_bonus.h"

static void	bmp_prepare(t_param *prm)
{
	t_render	*render;
	t_screen	*screen;

	render = prm->ptr;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	pic_export(prm, screen);
	mlx_destroy_image(render->mlx, render->img.img);
	render->img.img = NULL;
}

static void	bmp_render(t_ray *ray, t_param *prm)
{
	int			x;
	t_screen	*screen;

	x = 0;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	while (x < screen->width)
	{
		ray_init(x, ray, prm);
		ray_hit_scan(ray, prm);
		ray_perspective(ray, prm);
		ray_texture(ray, prm);
		draw_sky(x, ray, prm);
		draw_floor(x, ray, prm);
		fill_buffer(x, ray, prm);
		ray_fill_line_sprite(x, ray, prm);
		x++;
	}
}

int			pic_calculate(t_param *prm)
{
	t_ray		ray;
	t_render	*render;
	t_screen	*screen;
	t_list		*sprite;

	render = prm->ptr;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	sprite = get_lst_elem(prm->dlist, ID_SPRITES);
	render->img = my_mlx_new_image(render->mlx, screen->width, screen->height);
	sprite_calc_dist(prm);
	ft_sprite_sort((t_sprite**)&sprite->content);
	sprite_projection(prm);
	bmp_render(&ray, prm);
	bmp_prepare(prm);
	return (ft_exit(0, prm));
}
