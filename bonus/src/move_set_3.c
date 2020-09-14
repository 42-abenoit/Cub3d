/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_set_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 14:40:25 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/14 18:51:33 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub_macro.h"
#include "cub_struct.h"
#include "ft_utils.h"

void		ft_sneak(t_param *prm)
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

void		ft_sprint(t_param *prm)
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

void		ft_reset_conf(t_param *prm)
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
