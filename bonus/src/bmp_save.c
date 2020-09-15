/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 15:42:35 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/15 11:59:23 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mlx.h"
#include "cub3d.h"
#include "ft_utils.h"
#include "cub_macro.h"
#include "cub_struct.h"

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
	t_floor		floor;

	x = 0;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	while (x < screen->width)
	{
		ray_init(x, ray, prm);
		ray_hit_scan(ray, prm);
		ray_perspective(ray, prm);
		ray_texture(ray, prm);
		fill_sky_line(x, ray, prm);
		floor_init(&floor, ray);
		ray_fill_line_floor(x, &floor, ray, prm);
		fill_buffer(x, ray, prm);
		sprite_projection(prm);
		ray_fill_line_sprite(x, ray, prm);
		x++;
	}
}

int			pic_calculate(t_param *prm)
{
	t_ray		ray;
	t_render	*render;
	t_screen	*screen;
	t_sprite	*sprite;

	render = prm->ptr;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	sprite = get_lst_elem(prm->dlist, ID_SPRITES)->content;
	render->img = my_mlx_new_image(render->mlx, screen->width, screen->height);
	sprite_calc_dist(prm);
	ft_sprite_sort(&sprite);
	bmp_render(&ray, prm);
	bmp_prepare(prm);
	return (ft_exit(0, prm));
}
