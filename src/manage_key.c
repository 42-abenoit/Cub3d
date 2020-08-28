/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:04:58 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/28 12:04:06 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include "cub_macro.h"
#include "cub_struct.h"
#include "ft_utils.h"

int	ft_key_press(int keycode, t_param *prm)
{
	int			id;
	t_tx		*tx;
	t_render	*render;

	printf("%d\n", keycode);
	render = (t_render*)(prm->ptr);
	if (keycode == INPUT_ESC)
	{
		mlx_destroy_window(render->mlx, render->win);
		render->win = NULL;
	return (ft_exit(0, prm));
	}
	if (keycode == INPUT_UP)
	{
		id = ID_TX_NO;
		tx = (t_tx*)get_lst_elem(prm->dlist, id)->content;
		mlx_put_image_to_window(render->mlx, render->win, tx->data.img, 0, 0);
	}
	if (keycode == INPUT_DOWN)
	{
		id = ID_TX_SO;
		tx = (t_tx*)get_lst_elem(prm->dlist, id)->content;
		mlx_put_image_to_window(render->mlx, render->win, tx->data.img, 0, 0);
	}
	if (keycode == INPUT_LSTRAFE)
	{
		id = ID_TX_WE;
		tx = (t_tx*)get_lst_elem(prm->dlist, id)->content;
		mlx_put_image_to_window(render->mlx, render->win, tx->data.img, 0, 0);
	}
	if (keycode == INPUT_RSTRAFE)
	{
		id = ID_TX_EA;
		tx = (t_tx*)get_lst_elem(prm->dlist, id)->content;
		mlx_put_image_to_window(render->mlx, render->win, tx->data.img, 0, 0);
	}
	if (keycode == INPUT_LEFT)
	{
		id = ID_TX_S;
		tx = (t_tx*)get_lst_elem(prm->dlist, id)->content;
		mlx_put_image_to_window(render->mlx, render->win, tx->data.img, 0, 0);
	}
	return (0);
}
