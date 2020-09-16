/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_set_2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:58:08 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/16 13:33:49 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d_bonus.h"
#include "cub_macro_bonus.h"
#include "cub_struct_bonus.h"
#include "ft_utils_bonus.h"

void	ft_look_up(t_param *prm)
{
	t_player	*player;
	t_conf		*conf;
	t_screen	*screen;
	t_render	*render;
	double		rot_speed;

	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	render = (t_render*)prm->ptr;
	rot_speed = render->frame_time * conf->pitch_sensi;
	player->pitch += rot_speed;
	if (player->pitch > screen->height / 2)
		player->pitch = screen->height / 2;
}

void	ft_look_down(t_param *prm)
{
	t_player	*player;
	t_conf		*conf;
	t_screen	*screen;
	t_render	*render;
	double		rot_speed;

	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	render = (t_render*)prm->ptr;
	rot_speed = render->frame_time * conf->pitch_sensi;
	player->pitch -= rot_speed;
	if (player->pitch < -screen->height / 2)
		player->pitch = -screen->height / 2;
}

void	ft_rotate_right(t_param *prm)
{
	double		old_dir_x;
	t_player	*player;
	t_conf		*conf;
	t_render	*render;
	double		rot_speed;

	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	render = (t_render*)prm->ptr;
	rot_speed = render->frame_time * conf->rot_speed;
	old_dir_x = player->dir.x;
	player->dir.x = (player->dir.x * cos(rot_speed))
				- (player->dir.y * sin(rot_speed));
	player->dir.y = (old_dir_x * sin(rot_speed))
				+ (player->dir.y * cos(rot_speed));
	player->plane.x = -player->dir.y * ((player->view_angle * M_PI) / 180.0);
	player->plane.y = player->dir.x * ((player->view_angle * M_PI) / 180.0);
}

void	ft_rotate_left(t_param *prm)
{
	double		old_dir_x;
	t_player	*player;
	t_conf		*conf;
	t_render	*render;
	double		rot_speed;

	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	render = (t_render*)prm->ptr;
	rot_speed = render->frame_time * conf->rot_speed;
	old_dir_x = player->dir.x;
	player->dir.x = (player->dir.x * cos(-rot_speed))
				- (player->dir.y * sin(-rot_speed));
	player->dir.y = (old_dir_x * sin(-rot_speed))
				+ (player->dir.y * cos(-rot_speed));
	player->plane.x = -player->dir.y * ((player->view_angle * M_PI) / 180.0);
	player->plane.y = player->dir.x * ((player->view_angle * M_PI) / 180.0);
}
