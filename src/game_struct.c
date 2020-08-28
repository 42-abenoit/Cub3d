/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 16:51:32 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/28 16:59:02 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"
#include "cub_struct.h"
#include "cub_macro.h"
#include "ft_utils.h"
#include "mlx.h"
#ifdef Darwin
# ifdef bonus
#  include <CoreGraphics/CGDisplayConfiguration.h>
# endif
#endif

static int		tx_mlx_import(t_param *prm)
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

static void		screen_resize(t_param *prm)
{
	int			width;
	int			height;
	int			display_id;
	t_render	*render;
	t_screen	*screen;

	render = (t_render*)(prm->ptr);
	screen = (t_screen*)get_lst_elem(prm->dlist, ID_RES)->content;
	if (SYS == 1)
	{
		width = 2560;
		height = 1440;
	}
	else if (SYS == 2)
	{
		display_id = CGMainDisplayID();
		width = CGDisplayPixelsWide(display_id);
		height = CGDisplayPixelsHigh(display_id);
	}
	else
		mlx_get_screen_size(render->mlx, &width, &height);
	if (screen->width > width)
		screen->width = width;
	if (screen->height > height)
		screen->height = height;
}

static int		conf_init(t_param *prm)
{
	t_conf		*conf;

	if (!(conf = malloc(sizeof(t_conf))))
		return (MAL_ERR_CONF);
	if (SYS == 3 || SYS == 4)
	{
	conf->pitch_sensi = 0.1;
	conf->jump_height = 0.5;
	}
	conf->front_speed = 0.03;
	conf->back_speed = 0.01;
	conf->strafe_speed = 0.02;
	conf->rot_speed = 0.02;
	ft_lstadd_back(&(prm->dlist), ft_lstnew(ID_CONF, conf));
	if (get_lst_elem(prm->dlist, ID_CONF) == NULL)
		return (MAL_ERR_LIST);
	return (0);
}

static int		launch_main_loop(t_param *prm)
{
	t_render	*render;

	render = (t_render*)(prm->ptr);
	mlx_hook(render->win, 2, 1L << 0, ft_key_press, prm);
	mlx_hook(render->win, 3, 1L << 1, ft_key_release, prm);
	mlx_loop_hook(render->mlx, ray_caster, prm);
	mlx_loop(render->mlx);
	return (ft_exit(0, prm));
}

int				game_struct_init(t_param *prm)
{
	int			ret;
	t_render	*render;
	t_screen	*screen;

	if (!(render = malloc(sizeof(t_render))))
		return (ft_exit(MAL_ERR_RENDER, prm));
	render->mlx = mlx_init();
	if (render->mlx == NULL)
		return (MLX_INIT_FAIL);
	prm->ptr = render;
	prm->booleans += START_RENDER;
	if ((ret = tx_mlx_import(prm)) < 0)
		return (ft_exit(ret, prm));
	screen_resize(prm);
	if (prm->booleans & BMP_SAVE)
		return (printf("PLACEHOLDER : SAVE\n"));
	if ((ret = conf_init(prm)) < 0)
		return (ft_exit(ret, prm));
	screen = (t_screen*)get_lst_elem(prm->dlist, ID_RES)->content;
	render->win = mlx_new_window(render->mlx, screen->width,
									screen->height, "Cub3D");
	return (launch_main_loop(prm));
}
