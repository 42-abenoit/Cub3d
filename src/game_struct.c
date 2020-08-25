/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 16:51:32 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/25 18:05:50 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"
#include "cub_struct.h"
#include "cub_macro.h"
#include "ft_utils.h"

int		game_struct_init(t_param *prm)
{
	t_render	*render;

	if (!(render = malloc(sizeof(t_render))))
		return (ft_exit(MAL_ERR_RENDER, prm));
//	render->mlx = mlx_init();
//	if (render->mlx == NULL)
//		return (MLX_INIT_FAIL);
	prm->ptr = render;
	prm->booleans += START_RENDER;
	return (ft_exit(0, prm));
}
