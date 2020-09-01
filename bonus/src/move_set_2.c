/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_set_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:58:08 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/01 18:55:08 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include "cub_macro.h"
#include "cub_struct.h"
#include "ft_utils.h"

void	ft_look_up(t_param *prm)
{
	t_player	*player;
	t_conf		*conf;

	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	player->pitch += conf->pitch_sensi;
	if (player->pitch > 300)
		player->pitch = 300;
}

void	ft_look_down(t_param *prm)
{
	t_player	*player;
	t_conf		*conf;

	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	player->pitch -= conf->pitch_sensi;
	if (player->pitch < -300)
		player->pitch = -300;
}

void	ft_rotate_right(t_param *prm)
{
	double		old_dir_x;
	t_player	*player;
	t_conf		*conf;

	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	old_dir_x = player->dir.x;
	player->dir.x = (player->dir.x * cos(conf->rot_speed))
				- (player->dir.y * sin(conf->rot_speed));
	player->dir.y = (old_dir_x * sin(conf->rot_speed))
				+ (player->dir.y * cos(conf->rot_speed));
	player->plane.x = -player->dir.y * ((player->view_angle * M_PI) / 180.0);
	player->plane.y = player->dir.x * ((player->view_angle * M_PI) / 180.0);
}

void	ft_rotate_left(t_param *prm)
{
	double		old_dir_x;
	t_player	*player;
	t_conf		*conf;

	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	old_dir_x = player->dir.x;
	player->dir.x = (player->dir.x * cos(-conf->rot_speed))
				- (player->dir.y * sin(-conf->rot_speed));
	player->dir.y = (old_dir_x * sin(-conf->rot_speed))
				+ (player->dir.y * cos(-conf->rot_speed));
	player->plane.x = -player->dir.y * ((player->view_angle * M_PI) / 180.0);
	player->plane.y = player->dir.x * ((player->view_angle * M_PI) / 180.0);
}
