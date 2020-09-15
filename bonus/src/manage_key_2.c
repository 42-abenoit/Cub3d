/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_key_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 15:54:46 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/15 15:55:22 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub_macro.h"
#include "cub_struct.h"
#include "ft_utils.h"

static void	ft_release_map(int keycode, t_param *prm)
{
	if (keycode == INPUT_MAP)
	{
		if (prm->flags & FLAG_MAP)
			prm->flags -= FLAG_MAP;
		else if (prm->flags & FLAG_AXE)
		{
			if (!(prm->flags & FLAG_STRIKE))
			{
				prm->flags -= FLAG_AXE;
				prm->flags += FLAG_MAP;
			}
		}
		else
			prm->flags += FLAG_MAP;
	}
}

static void	ft_release_axe(int keycode, t_param *prm)
{
	if (keycode == INPUT_AXE)
	{
		if (prm->flags & FLAG_AXE)
		{
			if (!(prm->flags & FLAG_STRIKE))
				prm->flags -= FLAG_AXE;
		}
		else if (prm->flags & FLAG_MAP)
		{
			prm->flags -= FLAG_MAP;
			prm->flags += FLAG_AXE;
		}
		else
			prm->flags += FLAG_AXE;
	}
	if (keycode == INPUT_STRIKE && (prm->flags & FLAG_AXE))
	{
		if ((prm->flags & FLAG_STRIKE))
			prm->flags -= FLAG_STRIKE;
	}
}

static void	ft_release_special(int keycode, t_param *prm)
{
	if (keycode == INPUT_JUMP && (prm->flags & FLAG_JUMP))
	{
		if (!(prm->flags & FLAG_FALL))
			prm->flags += FLAG_FALL;
	}
	if (keycode == INPUT_SNEAK && (prm->flags & FLAG_SNEAK))
		prm->flags -= FLAG_SNEAK;
	if (keycode == INPUT_SPRINT && (prm->flags & FLAG_SPRINT))
		prm->flags -= FLAG_SPRINT;
}

int			ft_key_release(int keycode, t_param *prm)
{
	if (keycode == INPUT_UP && prm->flags & FLAG_UP)
		prm->flags -= FLAG_UP;
	if (keycode == INPUT_DOWN && prm->flags & FLAG_DOWN)
		prm->flags -= FLAG_DOWN;
	if (keycode == INPUT_LSTRAFE && prm->flags & FLAG_LSTRAFE)
		prm->flags -= FLAG_LSTRAFE;
	if (keycode == INPUT_RSTRAFE && prm->flags & FLAG_RSTRAFE)
		prm->flags -= FLAG_RSTRAFE;
	if (keycode == INPUT_LEFT && prm->flags & FLAG_LEFT)
		prm->flags -= FLAG_LEFT;
	if (keycode == INPUT_RIGHT && prm->flags & FLAG_RIGHT)
		prm->flags -= FLAG_RIGHT;
	if (keycode == INPUT_LOOK_UP && (prm->flags & FLAG_LOOK_UP))
		prm->flags -= FLAG_LOOK_UP;
	if (keycode == INPUT_LOOK_DOWN && (prm->flags & FLAG_LOOK_DOWN))
		prm->flags -= FLAG_LOOK_DOWN;
	ft_release_map(keycode, prm);
	ft_release_axe(keycode, prm);
	ft_release_special(keycode, prm);
	return (0);
}
