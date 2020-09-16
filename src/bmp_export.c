/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:34:00 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/16 14:58:09 by abenoit          ###   ########.fr       */
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
	int			tmp;
	int			ret;
	t_screen	*screen;

	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	tmp = 0x42;
	ret = write(fd, &tmp, 1);
	tmp = 0x4D;
	ret = write(fd, &tmp, 1);
	tmp = (screen->height * screen->width) * 4 + 14 + 40;
	ret = write(fd, &tmp, 4);
	tmp = 0;
	ret = write(fd, &tmp, 2);
	ret = write(fd, &tmp, 2);
	tmp = 54;
	ret = write(fd, &tmp, 4);
	if (ret < 0)
		return ;
}

static void	fill_dib_header(int fd, t_param *prm)
{
	int			tmp;
	int			ret;
	t_screen	*screen;

	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	tmp = 40;
	ret = write(fd, &tmp, 4);
	tmp = screen->width;
	ret = write(fd, &tmp, 4);
	tmp = screen->height;
	ret = write(fd, &tmp, 4);
	tmp = 1;
	ret = write(fd, &tmp, 2);
	tmp = 32;
	ret = write(fd, &tmp, 2);
	tmp = 0;
	ret = write(fd, &tmp, 4);
	ret = write(fd, &tmp, 4);
	ret = write(fd, &tmp, 4);
	ret = write(fd, &tmp, 4);
	ret = write(fd, &tmp, 4);
	ret = write(fd, &tmp, 4);
	if (ret < 0)
		return ;
}

void		pic_export(t_ray *ray, t_param *prm, t_screen *screen)
{
	int			fd;
	mode_t		mode;
	int			x;
	int			y;
	int			tmp;

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
			if (write(fd, &tmp, 4) < 0)
				return ;
			x++;
		}
		y--;
	}
}
