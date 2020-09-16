/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_anim_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 16:00:11 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/16 13:30:27 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "cub3d_bonus.h"
#include "ft_utils_bonus.h"
#include "cub_macro_bonus.h"
#include "cub_struct_bonus.h"

static void	check_hit(t_param *prm)
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
			if (ptr->dist < 1.0)
			{
				angle.x = ptr->pos.x - player->pos.x;
				angle.y = ptr->pos.y - player->pos.y;
				dot = (angle.x * player->dir.x) + (angle.y * player->dir.y);
				if (cos(1.0) < dot)
				{
					ptr->hit = 1;
					ptr->hp -= (rand() % 2) + 5;
				}
				if (ptr->hp <= 0)
					ptr->type = 1;
			}
		ptr = ptr->next;
	}
}

void		ft_axe_phase(t_param *prm)
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

static void	map_anim_phase(t_param *prm)
{
	t_player	*player;
	t_screen	*screen;

	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
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
		player->pitch = 0.9 * (-screen->height / 2);
	}
	if (player->anim_phase == 11)
		player->anim_phase = 0;
}

void		ft_map_phase(t_param *prm)
{
	t_player	*player;

	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
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
	map_anim_phase(prm);
}
