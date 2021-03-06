/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_valid_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 14:37:43 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/23 11:31:42 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cub3d_bonus.h"
#include "cub_macro_bonus.h"
#include "cub_struct_bonus.h"
#include "ft_utils_bonus.h"

static int	move_valid_sprites(t_param *prm, double pos_x, double pos_y)
{
	t_sprite	*ptr;
	double		new_dist;

	ptr = get_lst_elem(prm->dlist, ID_SPRITES)->content;
	while (ptr != NULL)
	{
		new_dist = ((pos_x - ptr->pos.x)
					* (pos_x - ptr->pos.x)
					+ (pos_y - ptr->pos.y)
					* (pos_y - ptr->pos.y));
		if (new_dist < 0.4)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

static int	move_valid_x(t_param *prm, double new_pos_x)
{
	t_map		*map;
	t_player	*player;

	map = get_lst_elem(prm->dlist, ID_MAP)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	if ((ft_isset(map->grid[(int)(player->pos.y)]
		[(int)new_pos_x], MAP_WALKABLE)))
		return (move_valid_sprites(prm, new_pos_x, player->pos.y));
	else
		return (0);
}

static int	move_valid_y(t_param *prm, double new_pos_y)
{
	t_map		*map;
	t_player	*player;

	map = get_lst_elem(prm->dlist, ID_MAP)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	if ((ft_isset(map->grid[(int)(new_pos_y)]
			[(int)player->pos.x], MAP_WALKABLE)))
		return (move_valid_sprites(prm, player->pos.x, new_pos_y));
	else
		return (0);
}

void		move_valid(t_param *prm, t_coord new_pos)
{
	t_player	*player;
	t_map		*map;

	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	map = get_lst_elem(prm->dlist, ID_MAP)->content;
	if (new_pos.y >= 0 && new_pos.y <= map->size_y)
		if (move_valid_y(prm, new_pos.y))
			player->pos.y = new_pos.y;
	if (new_pos.x >= 0 && new_pos.x <= ft_strlen(map->grid[(int)player->pos.y]))
		if (move_valid_x(prm, new_pos.x))
			player->pos.x = new_pos.x;
}
