/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 15:42:35 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/31 16:53:55 by abenoit          ###   ########.fr       */
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

static int	get_pic_color(int x, int y, t_data *img)
{
	int		color;
	char	*dst;

	dst = img->addr + (y * img->line_length + x * img->bits_per_pixel / 8);
	color = *(unsigned int*)dst;
	return (color);
}

static void	fill_bmp_header(int fd, t_param *prm)
{
	int tmp;
	t_screen	*screen;

	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	tmp = 0x42;
	write(fd, &tmp, 1);
	tmp = 0x4D;
	write(fd, &tmp, 1);
	tmp = (screen->height * screen->width) * 4 + 14 + 40;
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 2);
	write(fd, &tmp, 2);
	tmp = 54;
	write(fd, &tmp, 4);
}

static void	fill_dib_header(int fd, t_param *prm)
{
	int	tmp;
	t_screen	*screen;

	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	tmp = 40;
	write(fd, &tmp, 4);
	tmp = screen->width;
	write(fd, &tmp, 4);
	tmp = screen->height;
	write(fd, &tmp, 4);
	tmp = 1;
	write(fd, &tmp, 2);
	tmp = 32;
	write(fd, &tmp, 2);
	tmp = 0;
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
}

static void	pic_export(t_ray *ray, t_param *prm)
{
	int		fd;
	mode_t	mode;
	int		x;
	int		y;
	int		tmp;
	t_screen	*screen;
	t_render	*render;

	render = prm->ptr;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	mode = S_IRWXU | S_IRGRP | S_IROTH;
	fd = open("cub3d.bmp", O_RDWR | O_CREAT, mode);
	fill_bmp_header(fd, prm);
	fill_dib_header(fd, prm);
	y = screen->height - 1;
	while (y > -1)
	{
		x = 0;
		while (x < screen->width)
		{
			tmp = get_pic_color(x, y, &ray->img);
			write(fd, &tmp, 4);
			x++;
		}
		y--;
	}
	mlx_destroy_image(render->mlx, ray->img.img);
	ray->img.img = NULL;
}

int			pic_calculate(t_param *prm)
{
	t_ray		ray;
	t_screen	*screen;
	t_render	*render;
	int			x;

	x = 0;
	render = prm->ptr;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	ray.img = my_mlx_new_image(render->mlx, screen->width, screen->height);
	if (!(ray.line_buff = malloc(screen->height * sizeof(int))))
		return (MAL_ERR_BUFF);
	while (x < screen->width)
	{
		ray_init(x, &ray, prm);
		ray_step(&ray, prm);
		ray_hit_scan(&ray, prm);
		ray_perspective(&ray, prm);
		ray_texture(&ray, prm);
		fill_buffer(&ray, prm);
		sprite_projection(&ray, prm);
		ray_fill_line_sprite(x, &ray, prm);
		fill_line(x, &ray, prm);
		ft_clear_list(&ray.sprites);
		x++;
	}
	free(ray.line_buff);
	pic_export(&ray, prm);
	return (ft_exit(0, prm));
}
