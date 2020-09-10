/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 15:27:00 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/10 15:32:28 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub_struct.h"
#include "cub_macro.h"
#include "ft_utils.h"
#include <math.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t	mutex1 = PTHREAD_MUTEX_INITIALIZER;

void	sprite_calc_dist(t_param *prm)
{
	t_sprite	*ptr;
	t_player	*player;

	ptr = get_lst_elem(prm->dlist, ID_SPRITES)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	while (ptr != NULL)
	{
		ptr->dist = ((player->pos.x - ptr->pos.x)
					* (player->pos.x - ptr->pos.x)
					+ (player->pos.y - ptr->pos.y)
					* (player->pos.y - ptr->pos.y));
		ptr = ptr->next;
	}
}

static void	sprite_calc_draw_val(t_sprite *ptr, t_param *prm)
{
	t_screen	*screen;

	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	ptr->draw_start.y = -ptr->sprite_height / 2 + screen->height / 2
						+ ptr->v_move_screen;
	if (ptr->draw_start.y < 0)
		ptr->draw_start.y = 0;
	ptr->draw_end.y = ptr->sprite_height / 2 + screen->height / 2
						+ ptr->v_move_screen;
	if (ptr->draw_end.y >= screen->height)
		ptr->draw_end.y = screen->height - 1;
	ptr->sprite_width = abs((int)(screen->height / (ptr->transform.y)));
	ptr->draw_start.x = -ptr->sprite_width / 2 + ptr->sprite_screen_x;
	if (ptr->draw_start.x < 0)
		ptr->draw_start.x = 0;
	ptr->draw_end.x = ptr->sprite_width / 2 + ptr->sprite_screen_x;
	if (ptr->draw_end.x >= screen->width)
		ptr->draw_end.x = screen->width - 1;
}

void		sprite_projection(t_param *prm)
{
	t_sprite	*ptr;
	t_screen	*screen;
	t_player	*player;

	ptr = get_lst_elem(prm->dlist, ID_SPRITES)->content;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	while (ptr != NULL)
	{
		ptr->sprite.x = ptr->pos.x - player->pos.x;
		ptr->sprite.y = ptr->pos.y - player->pos.y;
		ptr->inv_det = 1.0 / (player->plane.x * player->dir.y
							- player->dir.x * player->plane.y);
		ptr->transform.x = ptr->inv_det * (player->dir.y * ptr->sprite.x
									- player->dir.x * ptr->sprite.y);
		ptr->transform.y = ptr->inv_det * (-player->plane.y * ptr->sprite.x
									+ player->plane.x * ptr->sprite.y);
		ptr->sprite_screen_x = (int)(((double)screen->width / 2)
							* (1 + ptr->transform.x / ptr->transform.y));
		ptr->v_move_screen = (int)(player->pitch + (player->pos_z / ptr->transform.y));
		ptr->sprite_height = abs((int)((double)screen->height
									/ (ptr->transform.y)));
		sprite_calc_draw_val(ptr, prm);
		ptr = ptr->next;
	}
}

static void	sprite_line_to_buff(t_sprite *ptr, t_tx	*tx, t_ray *ray, t_param *prm)
{
	int			y;
	int			d;
	t_screen	*screen;

	y = ptr->draw_start.y;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	while (y < ptr->draw_end.y)
	{
		d = (y - ptr->v_move_screen) * 256 - screen->height
				* 128 + ptr->sprite_height * 128;
		ptr->tex.y = (((d * tx->height)
					/ ptr->sprite_height) / 256)
			& (tx->height - 1);
		ray->color = get_pixel_color(ptr->tex.x, ptr->tex.y,
					&tx->data);
		ray->color = apply_fog(ptr->dist, ray->color, prm);
		if ((ray->color & 0x00FFFFFF) != 0)
			ray->line_buff[y] = ray->color;
		y++;
	}
}

void		ray_fill_line_sprite(int x, t_ray *ray, t_param *prm)
{
	t_sprite	*ptr;
	t_tx		*tx;
	t_screen	*screen;
	const int	types[] = {ID_TX_S, ID_TX_S2};

	ptr = get_lst_elem(prm->dlist, ID_SPRITES)->content;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	while (ptr != NULL)
	{
   		pthread_mutex_lock(&mutex1);
		if (x >= ptr->draw_start.x && x <= ptr->draw_end.x)
		{
			tx = get_lst_elem(prm->dlist, types[ptr->type])->content;
			ptr->tex.x = (int)((256 * (x - (-(double)ptr->sprite_width / 2
								+ (double)ptr->sprite_screen_x))
								* (double)tx->width
								/ (double)ptr->sprite_width)
								/ 256) & (tx->width - 1);
			if (ptr->transform.y > 0 && x > 0 && x
					< screen->width && ptr->transform.y < ray->perp_wall_dist)
				sprite_line_to_buff(ptr, tx, ray, prm);
		}
   		pthread_mutex_unlock(&mutex1);
		ptr = ptr->next;
	}
}
