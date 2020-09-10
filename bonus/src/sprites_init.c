/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 20:21:17 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/10 16:16:59 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "cub3d.h"
#include "cub_struct.h"
#include "cub_macro.h"
#include "ft_utils.h"

static int	create_sprite_dlist(t_param *prm, t_sprite *sprite)
{
	ft_lstadd_back(&(prm->dlist), ft_lstnew(ID_SPRITES, sprite));
	if (get_lst_elem(prm->dlist, ID_SPRITES) == NULL)
		return (MAL_ERR_LIST);
	return (0);
}

int			sprite_init(t_param *prm)
{
	t_sprite	*sprite;
	t_map		*map;
	int			ret;
	int			x;
	int			y;

	sprite = NULL;
	map = (t_map*)(get_lst_elem(prm->dlist, ID_MAP)->content);
	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == '2')
				ft_add_sprite_front(&sprite, ft_new_sprite(0, x, y));
			x++;
		}
		y++;
	}
	if ((ret = create_sprite_dlist(prm, sprite)) < 0)
		return (MAL_ERR_LIST);
	return (0);
}
