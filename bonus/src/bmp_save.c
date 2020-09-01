/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 15:42:35 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/01 18:24:59 by abenoit          ###   ########.fr       */
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

static void	bmp_prepare(t_ray *ray, t_param *prm)
{
	t_render	*render;
	t_screen	*screen;

	render = prm->ptr;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	pic_export(ray, prm, screen);
	mlx_destroy_image(render->mlx, ray->img.img);
	ray->img.img = NULL;
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
		fill_buffer(ray, prm);
		sprite_projection(prm);
		ray_fill_line_sprite(x, ray, prm);
		fill_line(x, ray, prm);
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
	ray.img = my_mlx_new_image(render->mlx, screen->width, screen->height);
	if (!(ray.line_buff = malloc(screen->height * sizeof(int))))
		return (MAL_ERR_BUFF);
	sprite_calc_dist(prm);
	ft_sprite_sort(&sprite);
	bmp_render(&ray, prm);
	free(ray.line_buff);
	bmp_prepare(&ray, prm);
	return (ft_exit(0, prm));
}
