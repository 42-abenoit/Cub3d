/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:04:58 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/31 17:15:26 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub_macro.h"
#include "cub_struct.h"
#include "ft_utils.h"

int		ft_key_press(int keycode, t_param *prm)
{
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
	return (0);
}

int		ft_key_release(int keycode, t_param *prm)
{
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
	return (0);
}

int		ft_move(t_param *prm)
{
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
