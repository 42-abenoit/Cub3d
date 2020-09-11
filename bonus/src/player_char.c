/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 11:49:23 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/11 14:57:17 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "cub3d.h"
#include "ft_utils.h"
#include "cub_macro.h"
#include "cub_struct.h"
#include <stdio.h>

void	player_to_screen(int x, t_ray *ray, t_param *prm)
{
	int		char_x;
	int		char_y;
	double	Rx;
	double	Ry;
	int		y;
	t_tx		*tx;
	t_player	*player;
	t_screen	*screen;
	const char	tx_id[] = {0, ID_TX_CA, ID_TX_CA1, ID_TX_CA2, ID_TX_CM};

	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	if (player->state == IDLE)
		return ;
	tx = get_lst_elem(prm->dlist, tx_id[player->state])->content;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	Rx = ((double)tx->width) / ((double)screen->width);
	Ry = ((double)tx->height) / ((double)screen->height);
	char_x = (int)floor(x * Rx);
	y = 0;
	while (y < screen->height)
	{
		char_y = (int)floor((double)y * Ry);
		ray->color = get_pixel_color(char_x, char_y, &tx->data);
		if ((ray->color & 0x00FFFFFF) != 0)
			ray->line_buff[y] = ray->color;
		y++;
	}
	if (player->state == MAP)
		minimap_to_screen(x, ray, prm);
}

void	check_hit(t_param *prm)
{
	t_sprite	*ptr;
	t_coord		angle;
	t_player	*player;
	double		dot;

	ptr = get_lst_elem(prm->dlist, ID_SPRITES)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	while (ptr != NULL)
	{
		if (ptr->type == 0)
		{
			if (ptr->dist < 1.0)
			{
				angle.x = ptr->pos.x - player->pos.x;
				angle.y = ptr->pos.y - player->pos.y;
				dot = (angle.x * player->dir.x) + (angle.y * player->dir.y);
	//		printf("%f\n", angle.x);
	//		printf("%f\n", angle.y);
	//		printf("%f\n", dot);
	//		printf("%f\n", cos(1.0));
				if (cos(1.0) < dot)
				{
					printf("hit\n");
					ptr->hp -= (rand() % 2) + 5;	
				}
				if (ptr->hp <= 0)
					ptr->type = 1;
			}
		}
		ptr = ptr->next;
	}
}

void	ft_axe_phase(t_param *prm)
{
	t_player	*player;

	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	if (!(prm->flags & FLAG_STRIKE))
	{
		if (player->anim_phase < 5)
			player->anim_phase += 1;
	}
	if (player->anim_phase < 3)
		player->state = ANIM1;
	else if (player->anim_phase == 3)
	{
		player->state = ANIM2;
		check_hit(prm);
	}
	else if (player->anim_phase == 5)
	{
		player->anim_phase = 0;
		if (prm->flags & FLAG_STRIKE)
			prm->flags -= FLAG_STRIKE;
	}
}

void	ft_map_phase(t_param *prm)
{
	t_player	*player;
	t_screen	*screen;

	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	if (prm->flags & FLAG_MAP)
	{
		if (player->anim_phase < 16)
			player->anim_phase += 1;
	}
	else
	{
		if (player->anim_phase > 11)
			player->anim_phase -= 1;
	}
	if (player->anim_phase == 12)
		player->pitch = 0.1 * (-screen->height / 2);
	else if (player->anim_phase == 13)
		player->pitch = 0.3 * (-screen->height / 2);
	else if (player->anim_phase == 14)
		player->pitch = 0.5 * (-screen->height / 2);
	else if (player->anim_phase == 15)
		player->pitch = 0.7 * (-screen->height / 2);
	else if (player->anim_phase == 16)
	{
		player->state = MAP;
		create_minimap(prm);
		player->pitch = 0.9 * (-screen->height / 2);
	}
	if (player->anim_phase == 11)
		player->anim_phase = 0;
}

void	ft_player_state(t_param *prm)
{
	t_player	*player;

	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	if (player->anim_phase > 0)
	{
		if (player->anim_phase < 10)
			ft_axe_phase(prm);
		else
			ft_map_phase(prm);
	}
	else if (prm->flags & FLAG_STRIKE)
		player->anim_phase = 1;
	else if (prm->flags & FLAG_AXE)
		player->state = AXE;
	else if (prm->flags & FLAG_MAP)
		player->anim_phase = 11;
	else
		player->state = IDLE;
}
