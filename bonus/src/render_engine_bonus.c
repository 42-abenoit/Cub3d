/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_engine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 16:16:35 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/23 11:20:58 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include "mlx.h"
#include "cub3d_bonus.h"
#include "ft_utils_bonus.h"
#include "cub_macro_bonus.h"
#include "cub_struct_bonus.h"

static void		cast_x_ray(int x, t_ray *ray, t_param *prm)
{
	ray_init(x, ray, prm);
	ray_hit_scan(ray, prm);
	ray_perspective(ray, prm);
	ray_texture(ray, prm);
	draw_sky(x, ray, prm);
	draw_floor(ray, prm);
	fill_buffer(ray, prm);
	ray_fill_line_sprite(x, ray, prm);
	player_to_screen(x, ray, prm);
	fill_line(x, ray, prm);
}

static void		*thread_range(void *thread)
{
	t_ray		ray;
	t_screen	*screen;
	int			x;
	int			x_max;

	screen = get_lst_elem(((t_thread*)thread)->prm->dlist, ID_RES)->content;
	x_max = (double)(screen->width + 1) / (double)NTHREAD;
	x = (double)((t_thread*)thread)->id_thread * x_max;
	if (((t_thread*)thread)->id_thread == NTHREAD - 1)
		x_max = screen->width;
	else
		x_max += x;
	if (!(ray.line_buff = malloc(screen->height * sizeof(int))))
	{
		((t_thread*)thread)->id_thread = -1;
		pthread_exit(NULL);
	}
	while (x < screen->width && x < x_max)
	{
		cast_x_ray(x, &ray, ((t_thread*)thread)->prm);
		x++;
	}
	free(ray.line_buff);
	pthread_exit(NULL);
}

static int		thread_manager(t_param *prm)
{
	int			i;
	pthread_t	thread[NTHREAD];
	t_thread	pthread_struct[NTHREAD];

	i = 0;
	while (i < NTHREAD)
	{
		pthread_struct[i].id_thread = i;
		pthread_struct[i].prm = prm;
		pthread_create(&thread[i], NULL, &thread_range, &pthread_struct[i]);
		i++;
	}
	while (--i > -1)
	{
		pthread_join(thread[i], NULL);
		if (pthread_struct[i].id_thread < 0)
			return (-1);
	}
	return (0);
}

int				ray_caster(t_param *prm)
{
	t_screen	*screen;
	t_render	*render;
	t_list		*sprite;
	clock_t		start;
	clock_t		end;

	render = prm->ptr;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	sprite = get_lst_elem(prm->dlist, ID_SPRITES);
	render->img = my_mlx_new_image(render->mlx, screen->width, screen->height);
	sprite_calc_dist(prm);
	ft_sprite_sort((t_sprite**)&sprite->content);
	sprite_projection(prm);
	start = clock();
	if (thread_manager(prm) < 0)
		return (ft_exit(MAL_ERR_BUFF, prm));
	img_refresh(prm);
	end = clock();
	render->frame_time = (double)(end - start) / CLOCKS_PER_SEC;
	ft_move(prm);
	return (0);
}
