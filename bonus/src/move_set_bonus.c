/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_set_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:46:35 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/16 13:33:27 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d_bonus.h"
#include "cub_macro_bonus.h"
#include "cub_struct_bonus.h"
#include "ft_utils_bonus.h"

void	ft_forward(t_param *prm)
{
	t_player	*player;
	t_conf		*conf;
	t_coord		new_pos;
	t_render	*render;
	double		speed;

	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	render = (t_render*)prm->ptr;
	speed = render->frame_time * conf->front_speed;
	new_pos.x = player->pos.x + (player->dir.x * speed);
	new_pos.y = player->pos.y + (player->dir.y * speed);
	move_valid(prm, new_pos);
}

void	ft_backward(t_param *prm)
{
	t_player	*player;
	t_conf		*conf;
	t_coord		new_pos;
	t_render	*render;
	double		speed;

	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	render = (t_render*)prm->ptr;
	speed = render->frame_time * conf->back_speed;
	new_pos.x = player->pos.x - (player->dir.x * speed);
	new_pos.y = player->pos.y - (player->dir.y * speed);
	move_valid(prm, new_pos);
}

void	ft_strafe_left(t_param *prm)
{
	t_player	*player;
	t_conf		*conf;
	t_coord		new_pos;
	t_render	*render;
	double		speed;

	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	render = (t_render*)prm->ptr;
	speed = render->frame_time * conf->strafe_speed;
	new_pos.x = player->pos.x + (player->dir.y * speed);
	new_pos.y = player->pos.y - (player->dir.x * speed);
	move_valid(prm, new_pos);
}

void	ft_strafe_right(t_param *prm)
{
	t_player	*player;
	t_conf		*conf;
	t_coord		new_pos;
	t_render	*render;
	double		speed;

	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	render = (t_render*)prm->ptr;
	speed = render->frame_time * conf->strafe_speed;
	new_pos.x = player->pos.x - (player->dir.y * speed);
	new_pos.y = player->pos.y + (player->dir.x * speed);
	move_valid(prm, new_pos);
}
