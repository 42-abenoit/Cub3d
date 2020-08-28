/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:04:58 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/28 17:40:45 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub_macro.h"
#include "cub_struct.h"
#include "ft_utils.h"

int	ft_key_press(int keycode, t_param *prm)
{
	t_player	*player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	if (keycode == INPUT_ESC)
		return (ft_exit(0, prm));
	if (keycode == INPUT_UP && !(prm->booleans & FLAG_UP))
		prm->booleans += FLAG_UP;
	if (keycode == INPUT_DOWN && !(prm->booleans & FLAG_DOWN))
		prm->booleans += FLAG_DOWN;
	if (keycode == INPUT_LSTRAFE && !(prm->booleans & FLAG_LSTRAFE))
		prm->booleans += FLAG_LSTRAFE;
	if (keycode == INPUT_RSTRAFE && !(prm->booleans & FLAG_RSTRAFE))
		prm->booleans += FLAG_RSTRAFE;
	if (keycode == INPUT_LEFT && !(prm->booleans & FLAG_LEFT))
		prm->booleans += FLAG_LEFT;
	if (keycode == INPUT_RIGHT && !(prm->booleans & FLAG_RIGHT))
		prm->booleans += FLAG_RIGHT;
	if (keycode == INPUT_STRIKE && !(prm->booleans & FLAG_JUMP))
	{
		prm->booleans += FLAG_JUMP;
		player->pos_z = 100.0;
	}
	if (keycode == INPUT_AXE && !(prm->booleans & FLAG_AXE))
		prm->booleans += FLAG_AXE;
	if (keycode == INPUT_MAP && !(prm->booleans & FLAG_MAP))
		prm->booleans += FLAG_MAP;
	return (0);
}

int		ft_key_release(int keycode, t_param *prm)
{
	t_player	*player = get_lst_elem(prm->dlist, ID_PLAYER)->content;

	if (keycode == INPUT_UP && prm->booleans & FLAG_UP)
		prm->booleans -= FLAG_UP;
	if (keycode == INPUT_DOWN && prm->booleans & FLAG_DOWN)
		prm->booleans -= FLAG_DOWN;
	if (keycode == INPUT_LSTRAFE && prm->booleans & FLAG_LSTRAFE)
		prm->booleans -= FLAG_LSTRAFE;
	if (keycode == INPUT_RSTRAFE && prm->booleans & FLAG_RSTRAFE)
		prm->booleans -= FLAG_RSTRAFE;
	if (keycode == INPUT_LEFT && prm->booleans & FLAG_LEFT)
		prm->booleans -= FLAG_LEFT;
	if (keycode == INPUT_RIGHT && prm->booleans & FLAG_RIGHT)
		prm->booleans -= FLAG_RIGHT;
	if (keycode == INPUT_STRIKE && (prm->booleans & FLAG_JUMP))
	{
		prm->booleans -= FLAG_JUMP;
		player->pos_z = 0.0;
	}
	if (keycode == INPUT_AXE && (prm->booleans & FLAG_AXE))
	{
		prm->booleans -= FLAG_AXE;
		player->pitch = 0.0;
	}
	if (keycode == INPUT_MAP && (prm->booleans & FLAG_MAP))
	{
		prm->booleans -= FLAG_MAP;
		player->pitch = 0.0;
	}
	return (0);
}

int		ft_move(t_param *prm)
{
	t_player	*player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	if (prm->booleans & FLAG_AXE)
		player->pitch += 1.0;
	if (prm->booleans & FLAG_MAP)
		player->pitch -= 1.0;
	if (prm->booleans & FLAG_UP)
		ft_forward(prm);
	if (prm->booleans & FLAG_DOWN)
		ft_backward(prm);
	if (prm->booleans & FLAG_LSTRAFE)
		ft_strafe_left(prm);
	if (prm->booleans & FLAG_RSTRAFE)
		ft_strafe_right(prm);
	if (prm->booleans & FLAG_LEFT)
		ft_rotate_left(prm);
	if (prm->booleans & FLAG_RIGHT)
		ft_rotate_right(prm);
	return (0);
}
