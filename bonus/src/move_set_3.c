/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_set_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 14:40:25 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/10 14:43:50 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub_macro.h"
#include "cub_struct.h"
#include "ft_utils.h"

void	ft_jump(t_param *prm)
{
	t_player	*player;
	t_conf		*conf;
	double		height;

	height = 0;
	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	if (!(prm->flags & FLAG_FALL))
		player->jump_phase += 1;
	else
		player->jump_phase -= 1;
	if (player->jump_phase == 0)
	{
		height = 0;
		if (player->jump_max < 3 || prm->flags & FLAG_SNEAK)
		{
			if (prm->flags & FLAG_FALL)
				prm->flags -= FLAG_FALL;
			prm->flags -= FLAG_JUMP;
			player->jump_phase = 0;
			player->jump_max = 0;
		}
	}
	else if (player->jump_phase == -1)
		height = -0.05;
	else if (player->jump_phase == -2)
		height = -0.1;
	else if (player->jump_phase == -3)
		height = -0.05;
	else if (player->jump_phase == -4)
	{
		if (prm->flags & FLAG_FALL)
			prm->flags -= FLAG_FALL;
		prm->flags -= FLAG_JUMP;
		player->jump_phase = 0;
		player->jump_max = 0;
	}
	else if (player->jump_phase == 1)
		height = -0.08 * conf->jump_height;
	else if (player->jump_phase == 2)
		height = 0.2 * conf->jump_height;
	else if (player->jump_phase == 3)
		height = 0.5 * conf->jump_height;
	else if (player->jump_phase == 4)
		height = 0.7 * conf->jump_height;
	else if (player->jump_phase == 5)
		height = 0.85 * conf->jump_height;
	else if (player->jump_phase == 6)
		height = 0.95 * conf->jump_height;
	else if (player->jump_phase == 7)
	{
		height = 1.0 * conf->jump_height;
		if (!(prm->flags & FLAG_FALL))
			prm->flags += FLAG_FALL;
	}
	if (player->jump_phase > player->jump_max)
		player->jump_max = player->jump_phase;
	player->pos_z = height;
}

void	ft_sneak(t_param *prm)
{
	t_player	*player;
	t_conf		*conf;

	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	if (prm->flags & FLAG_SNEAK)
	{
		if (!(prm->flags & FLAG_JUMP))
		{
			player->pos_z = -0.3 * conf->jump_height;
			conf->front_speed = 1.7;
			conf->back_speed = 1.2;
			conf->strafe_speed = 1.5;
		}
	}
}

void	ft_sprint(t_param *prm)
{
	t_player	*player;
	t_conf		*conf;

	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	if (prm->flags & FLAG_SPRINT)
	{
		if (!(prm->flags & FLAG_JUMP))
		{
			player->pos_z = -0.05 * conf->jump_height;
			conf->front_speed = 4.5;
			conf->back_speed = 2.2;
			conf->strafe_speed = 4.0;
			conf->rot_speed = 1.0;
		}
	}
}

void	ft_reset_conf(t_param *prm)
{
	t_player	*player;
	t_conf		*conf;

	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	if (!(prm->flags & FLAG_SPRINT)
		&& !(prm->flags & FLAG_SNEAK)
		&& !(prm->flags & FLAG_JUMP))
	{
		player->pos_z = 0;
		conf->front_speed = 3.0;
		conf->back_speed = 2.0;
		conf->strafe_speed = 2.6;
		conf->rot_speed = 2.0;
	}
}
