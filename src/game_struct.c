/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 16:51:32 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/24 20:35:04 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub_struct.h"
#include "cub_macro.h"
#include "ft_utils.h"

int		game_struct_init(t_param *prm)
{
	int		ret;

	if ((ret = player_init(prm)) < 0)
		return (ft_exit(ret, prm));
	return (ft_exit(0, prm));
}
