/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_engine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 16:16:35 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/17 18:44:36 by abenoit          ###   ########.fr       */
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

static void		*cast_x_rays(void *thread)
{
	t_ray		ray;
	t_screen	*screen;
	int			x;
	int			x_max;
	double		tmp;

	screen = get_lst_elem(((t_thread*)thread)->prm->dlist, ID_RES)->content;
	tmp = (double)((t_thread*)thread)->id_thread
				* ((double)(screen->width + 1) / (double)NTHREAD);
	x_max = (double)tmp + ((double)(screen->width + 1) / (double)NTHREAD);
	x = (int)tmp;
	while (x < x_max)
	{
		ray_init(x, &ray, ((t_thread*)thread)->prm);
		ray_hit_scan(&ray, ((t_thread*)thread)->prm);
		ray_perspective(&ray, ((t_thread*)thread)->prm);
		ray_texture(&ray, ((t_thread*)thread)->prm);
		draw_sky(x, &ray, ((t_thread*)thread)->prm);
		draw_floor(x, &ray, ((t_thread*)thread)->prm);
		fill_buffer(x, &ray, ((t_thread*)thread)->prm);
		ray_fill_line_sprite(x, &ray, ((t_thread*)thread)->prm);
		player_to_screen(x, &ray, ((t_thread*)thread)->prm);
		x++;
	}
	pthread_exit(NULL);
}

static void		thread_manager(t_param *prm)
{
	int			i;
	pthread_t	thread[NTHREAD];
	t_thread	plop[NTHREAD];

	i = 0;
	while (i < NTHREAD)
	{
		plop[i].id_thread = i;
		plop[i].prm = prm;
		pthread_create(&thread[i], NULL, &cast_x_rays, &plop[i]);
		i++;
	}
	while (--i > -1)
		pthread_join(thread[i], NULL);
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
	thread_manager(prm);
	img_refresh(prm);
	end = clock();
	render->frame_time = (double)(end - start) / CLOCKS_PER_SEC;
	ft_move(prm);
	return (0);
}
