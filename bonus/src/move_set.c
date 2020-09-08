/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:46:35 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/08 18:59:01 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include "cub_macro.h"
#include "cub_struct.h"
#include "ft_utils.h"

void	ft_forward(t_param *prm)
{
	t_player	*player;
	t_map		*map;
	t_conf		*conf;
	t_render	*render;
	double		speed;

	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	map = get_lst_elem(prm->dlist, ID_MAP)->content;
	render = (t_render*)prm->ptr;
	speed = render->frame_time * conf->front_speed; 
	if ((int)(player->pos.y) >= 0 && (int)(player->pos.y) <= map->size_y
			&& (int)(player->pos.x + player->dir.x * speed) >= 0
			&& (int)(player->pos.x + player->dir.x * speed)
				<= map->size_x && (int)(player->pos.x) >= 0
			&& (int)(player->pos.x) <= map->size_x
			&& (int)(player->pos.y + player->dir.y * speed) >= 0
			&& (int)(player->pos.y + player->dir.y * speed)
				<= map->size_y)
	{
		if (!ft_isset(map->grid[(int)(player->pos.y)]
				[(int)(player->pos.x + player->dir.x * speed)],
					MAP_OBSTACLE))
			player->pos.x += player->dir.x * speed;
		if (!ft_isset(map->grid[(int)(player->pos.y
			+ player->dir.y * speed)]
			[(int)(player->pos.x)], MAP_OBSTACLE))
			player->pos.y += player->dir.y * speed;
	}
}

void	ft_backward(t_param *prm)
{
	t_player	*player;
	t_map		*map;
	t_conf		*conf;
	t_render	*render;
	double		speed;

	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	map = get_lst_elem(prm->dlist, ID_MAP)->content;
	render = (t_render*)prm->ptr;
	speed = render->frame_time * conf->back_speed; 
	if ((int)(player->pos.y) >= 0 && (int)(player->pos.y) <= map->size_y
			&& (int)(player->pos.x - player->dir.x * speed) >= 0
			&& (int)(player->pos.x - player->dir.x * speed)
				<= map->size_x && (int)(player->pos.x) >= 0
			&& (int)(player->pos.x) <= map->size_x
			&& (int)(player->pos.y - player->dir.y * speed) >= 0
			&& (int)(player->pos.y - player->dir.y * speed)
				<= map->size_y)
	{
		if (!ft_isset(map->grid[(int)(player->pos.y)]
				[(int)(player->pos.x - player->dir.x * speed)],
					MAP_OBSTACLE))
			player->pos.x -= player->dir.x * speed;
		if (!ft_isset(map->grid[(int)(player->pos.y
								- player->dir.y * speed)]
								[(int)(player->pos.x)], MAP_OBSTACLE))
			player->pos.y -= player->dir.y * speed;
	}
}

void	ft_strafe_left(t_param *prm)
{
	t_player	*player;
	t_map		*map;
	t_conf		*conf;
	t_render	*render;
	double		speed;

	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	map = get_lst_elem(prm->dlist, ID_MAP)->content;
	render = (t_render*)prm->ptr;
	speed = render->frame_time * conf->strafe_speed; 
	if ((int)(player->pos.y) >= 0 && (int)(player->pos.y) <= map->size_y
			&& (int)(player->pos.x + player->dir.y * speed) >= 0
			&& (int)(player->pos.x + player->dir.y * speed)
				<= map->size_x && (int)(player->pos.x) >= 0
			&& (int)(player->pos.x) <= map->size_x
			&& (int)(player->pos.y - player->dir.x * speed) >= 0
			&& (int)(player->pos.y - player->dir.x * speed)
				<= map->size_y)
	{
		if (!ft_isset(map->grid[(int)(player->pos.y)]
				[(int)(player->pos.x + player->dir.y * speed)],
						MAP_OBSTACLE))
			player->pos.x += player->dir.y * speed;
		if (!ft_isset(map->grid[(int)(player->pos.y
								- player->dir.x * speed)]
								[(int)(player->pos.x)], MAP_OBSTACLE))
			player->pos.y -= player->dir.x * speed;
	}
}

void	ft_strafe_right(t_param *prm)
{
	t_player	*player;
	t_map		*map;
	t_conf		*conf;
	t_render	*render;
	double		speed;

	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	map = get_lst_elem(prm->dlist, ID_MAP)->content;
	render = (t_render*)prm->ptr;
	speed = render->frame_time * conf->strafe_speed; 
	if ((int)(player->pos.y) >= 0 && (int)(player->pos.y) <= map->size_y
			&& (int)(player->pos.x - player->dir.y * speed) >= 0
			&& (int)(player->pos.x - player->dir.y * speed)
				<= map->size_x && (int)(player->pos.x) >= 0
			&& (int)(player->pos.x) <= map->size_x
			&& (int)(player->pos.y + player->dir.x * speed) >= 0
			&& (int)(player->pos.y + player->dir.x * speed)
				<= map->size_y)
	{
		if (!ft_isset(map->grid[(int)(player->pos.y)]
				[(int)(player->pos.x
				- player->dir.y * speed)], MAP_OBSTACLE))
			player->pos.x -= player->dir.y * speed;
		if (!ft_isset(map->grid[(int)(player->pos.y +
								player->dir.x * speed)]
								[(int)(player->pos.x)], MAP_OBSTACLE))
			player->pos.y += player->dir.x * speed;
	}
}

void	ft_jump(t_param *prm)
{
	t_player	*player;
	t_conf		*conf;
	double		height;

	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	if (!(prm->booleans & FLAG_FALL))
		player->jump_phase += 1;
	else
	{
		player->jump_phase -= 1;
	}
	if (player->jump_phase == 0)
		height = -0.1 * conf->jump_height;
	else if (player->jump_phase == -1)
		height = 0;
	else if (player->jump_phase == -2)
	{
		prm->booleans -= FLAG_FALL;
		prm->booleans -= FLAG_JUMP;
		player->jump_phase = 0;
	}
	else if (player->jump_phase == 1)
		height = 0.5 * conf->jump_height;
	else if (player->jump_phase == 2)
		height = 0.7 * conf->jump_height;
	else if (player->jump_phase == 3)
		height = 0.85 * conf->jump_height;
	else if (player->jump_phase == 4)
		height = 0.95 * conf->jump_height;
	else if (player->jump_phase == 5)
	{
		height = 1.0 * conf->jump_height;
		prm->booleans += FLAG_FALL;
	}
	player->pos_z = height;
}
