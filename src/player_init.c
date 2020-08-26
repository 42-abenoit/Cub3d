/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 20:21:17 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/26 16:12:28 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"
#include "cub_struct.h"
#include "cub_macro.h"
#include "ft_utils.h"

static int	player_clean_exit(int ret, t_ent *player)
{
	free(player);
	return (ret);
}

static void	player_set_dir(t_ent *player, int dir_x, int dir_y)
{
	player->view_angle = 33.0;
	player->dir.x = dir_x;
	player->dir.y = dir_y;
/*
**	equations for plane calculations :
**	plane.x = -dir_y * ((player->view_angle * M_PI) / 180);
**	plane.y = dir_x * ((player->view_angle * M_PI) / 180);
*/
}

static int	player_set_start(t_param *prm, int x, int y, t_ent *player)
{
	t_map	*map;
	char	dir;

	map = (t_map*)(get_lst_elem(prm->dlist, ID_MAP)->content);
	dir = map->grid[y][x];
	if (prm->booleans & START_SET)
		return (START_ALRD_SET);
	if (dir == 'N')
		player_set_dir(player, 0.0, -1.0);
	if (dir == 'S')
		player_set_dir(player, 0.0, 1.0);
	if (dir == 'W')
		player_set_dir(player, -1.0, 0.0);
	if (dir == 'E')
		player_set_dir(player, 1.0, 0.0);
	player->pos.x = x;
	player->pos.y = y;
	prm->booleans += START_SET;
	return (0);
}

static int	create_player_dlist(t_param *prm, t_ent *player)
{
	if (!(prm->booleans & START_SET))
			return(player_clean_exit(NO_START_POS, player));
	ft_lstadd_back(&(prm->dlist), ft_lstnew(ID_PLAYER, player));
	if (get_lst_elem(prm->dlist, ID_PLAYER) == NULL)
		return (player_clean_exit(MAL_ERR_LIST, player));
	return (0);
}

int			player_init(t_param *prm)
{
	t_ent	*player;
	t_map	*map;
	int		ret;
	int		x;
	int		y;

	if (!(player = malloc(sizeof(t_ent))))
		return (MAL_ERR_PLAYER);
	map = (t_map*)(get_lst_elem(prm->dlist, ID_MAP)->content);
	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (ft_isset(map->grid[y][x], MAP_START))
				if ((ret = player_set_start(prm, x, y, player)) < 0)
					return (player_clean_exit(ret, player));
			x++;
		}
		y++;
	}
	return (create_player_dlist(prm, player));
}
