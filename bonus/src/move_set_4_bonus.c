/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_set_4_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 18:50:55 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/16 13:34:37 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "cub_macro_bonus.h"
#include "cub_struct_bonus.h"
#include "ft_utils_bonus.h"

static void	jump_reception(t_param *prm)
{
	t_player	*player;

	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	if (prm->flags & FLAG_FALL)
		prm->flags -= FLAG_FALL;
	prm->flags -= FLAG_JUMP;
	player->jump_phase = 0;
	player->jump_max = 0;
}

static int	jump_anim_fall(double *height, t_param *prm)
{
	t_player	*player;

	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	if (player->jump_phase == 0)
	{
		*height = 0;
		if (player->jump_max < 3 || prm->flags & FLAG_SNEAK)
			jump_reception(prm);
	}
	else if (player->jump_phase == -1)
		*height = -0.05;
	else if (player->jump_phase == -2)
		*height = -0.1;
	else if (player->jump_phase == -3)
		*height = -0.05;
	else if (player->jump_phase == -4)
		jump_reception(prm);
	else
		return (0);
	return (1);
}

static void	jump_anim_ascension(double *height, t_param *prm)
{
	t_player	*player;
	t_conf		*conf;

	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	if (player->jump_phase == 1)
		*height = -0.08 * conf->jump_height;
	else if (player->jump_phase == 2)
		*height = 0.2 * conf->jump_height;
	else if (player->jump_phase == 3)
		*height = 0.5 * conf->jump_height;
	else if (player->jump_phase == 4)
		*height = 0.7 * conf->jump_height;
	else if (player->jump_phase == 5)
		*height = 0.85 * conf->jump_height;
	else if (player->jump_phase == 6)
		*height = 0.95 * conf->jump_height;
	else if (player->jump_phase == 7)
	{
		*height = 1.0 * conf->jump_height;
		if (!(prm->flags & FLAG_FALL))
			prm->flags += FLAG_FALL;
	}
}

void		ft_jump(t_param *prm)
{
	t_player	*player;
	double		height;

	height = 0;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	if (!(prm->flags & FLAG_FALL))
		player->jump_phase += 1;
	else
		player->jump_phase -= 1;
	if (!(jump_anim_fall(&height, prm)))
		jump_anim_ascension(&height, prm);
	if (player->jump_phase > player->jump_max)
		player->jump_max = player->jump_phase;
	player->pos_z = height;
}
