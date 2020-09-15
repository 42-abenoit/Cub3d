/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:04:58 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/15 15:56:25 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub_macro.h"
#include "cub_struct.h"
#include "ft_utils.h"

static void	ft_press_specials(int keycode, t_param *prm)
{
	if (keycode == INPUT_JUMP && !(prm->flags & FLAG_JUMP))
		prm->flags += FLAG_JUMP;
	if (keycode == INPUT_SNEAK && !(prm->flags & FLAG_SNEAK))
		prm->flags += FLAG_SNEAK;
	if (keycode == INPUT_SPRINT && !(prm->flags & FLAG_SPRINT))
		prm->flags += FLAG_SPRINT;
}

int			ft_key_press(int keycode, t_param *prm)
{
	if (keycode == INPUT_ESC)
		return (ft_exit(0, prm));
	if (keycode == INPUT_UP && !(prm->flags & FLAG_UP))
		prm->flags += FLAG_UP;
	if (keycode == INPUT_DOWN && !(prm->flags & FLAG_DOWN))
		prm->flags += FLAG_DOWN;
	if (keycode == INPUT_LSTRAFE && !(prm->flags & FLAG_LSTRAFE))
		prm->flags += FLAG_LSTRAFE;
	if (keycode == INPUT_RSTRAFE && !(prm->flags & FLAG_RSTRAFE))
		prm->flags += FLAG_RSTRAFE;
	if (keycode == INPUT_LEFT && !(prm->flags & FLAG_LEFT))
		prm->flags += FLAG_LEFT;
	if (keycode == INPUT_RIGHT && !(prm->flags & FLAG_RIGHT))
		prm->flags += FLAG_RIGHT;
	if (keycode == INPUT_LOOK_UP && !(prm->flags & FLAG_LOOK_UP))
		prm->flags += FLAG_LOOK_UP;
	if (keycode == INPUT_LOOK_DOWN && !(prm->flags & FLAG_LOOK_DOWN))
		prm->flags += FLAG_LOOK_DOWN;
	if (keycode == INPUT_STRIKE && (prm->flags & FLAG_AXE))
	{
		if (!(prm->flags & FLAG_STRIKE))
			prm->flags += FLAG_STRIKE;
	}
	ft_press_specials(keycode, prm);
	return (0);
}

int			ft_move(t_param *prm)
{
	ft_sneak(prm);
	ft_sprint(prm);
	ft_player_state(prm);
	ft_reset_conf(prm);
	if (prm->flags & FLAG_UP)
		ft_forward(prm);
	if (prm->flags & FLAG_DOWN)
		ft_backward(prm);
	if (prm->flags & FLAG_LSTRAFE)
		ft_strafe_left(prm);
	if (prm->flags & FLAG_RSTRAFE)
		ft_strafe_right(prm);
	if (prm->flags & FLAG_LEFT)
		ft_rotate_left(prm);
	if (prm->flags & FLAG_RIGHT)
		ft_rotate_right(prm);
	if (prm->flags & FLAG_LOOK_UP)
		ft_look_up(prm);
	if (prm->flags & FLAG_LOOK_DOWN)
		ft_look_down(prm);
	if (prm->flags & FLAG_JUMP || prm->flags & FLAG_FALL)
		ft_jump(prm);
	return (0);
}
