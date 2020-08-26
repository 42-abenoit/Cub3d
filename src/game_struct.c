/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 16:51:32 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/26 18:51:08 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"
#include "cub_struct.h"
#include "cub_macro.h"
#include "ft_utils.h"
#include "mlx.h"
#include <unistd.h>

#if OS_NAME==LINUX
#define OS 1
#elif OS_NAME==MACOS
#define OS 2
#endif

static int	tx_mlx_import(t_param *prm)
{
	int			id;
	int			ret;
	t_list		*ptr;
	t_render	*render;

	id = ID_TX_NO;
	render = (t_render*)prm->ptr;
	while (id <= ID_TX_S)
	{
		ptr = get_lst_elem(prm->dlist, id);
		if ((ret = my_mlx_tx_from_path(render->mlx, ptr)) < 0)
			return (ret);
		id++;
	}
	return (0);
}

int			game_struct_init(t_param *prm)
{
	int			ret;
	t_screen	*screen;
	t_render	*render;

	if (!(render = malloc(sizeof(t_render))))
		return (ft_exit(MAL_ERR_RENDER, prm));
	render->mlx = mlx_init();
	if (render->mlx == NULL)
		return (MLX_INIT_FAIL);
	prm->ptr = render;
	prm->booleans += START_RENDER;
	if ((ret = tx_mlx_import(prm)) < 0)
		return (ft_exit(ret, prm));
	screen = (t_screen*)get_lst_elem(prm->dlist, ID_RES)->content;
	if (OS == 1)
		return (printf("PLACEHOLDER : LINUX\n"));
	else if (OS == 2)
		return (printf("PLACEHOLDER : MACOS\n"));
	if (prm->booleans & BMP_SAVE)
		return (printf("PLACEHOLDER : SAVE\n"));
	render->win = mlx_new_window(render->mlx, screen->width,
									screen->height, "Cub3D");

	int			id;
	t_tx		*tx;

	id = ID_TX_NO;
	while (id <= ID_TX_S)
	{
		tx = (t_tx*)get_lst_elem(prm->dlist, id)->content;
		mlx_put_image_to_window(render->mlx, render->win, tx->data.img, 0, 0);	
		sleep(1);
		id++;
	}
	return (ft_exit(0, prm));
}
