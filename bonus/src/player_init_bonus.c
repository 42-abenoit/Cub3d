/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 20:21:17 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/17 18:31:32 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "cub3d_bonus.h"
#include "cub_struct_bonus.h"
#include "cub_macro_bonus.h"
#include "ft_utils_bonus.h"

static int	player_clean_exit(int ret, t_player *player)
{
	free(player);
	return (ret);
}

static void	player_set_dir(t_player *player, int dir_x, int dir_y)
{
	player->view_angle = 32.5;
	player->dir.x = dir_x;
	player->dir.y = dir_y;
	player->plane.x = -player->dir.y * ((player->view_angle * M_PI) / 180);
	player->plane.y = player->dir.x * ((player->view_angle * M_PI) / 180);
	player->pitch = 0.01;
	player->pos_z = 0;
	player->jump_phase = 0;
	player->jump_max = 0;
	player->state = 0;
	player->anim_phase = 0;
}

static int	player_set_start(t_param *prm, int x, int y, t_player *player)
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
	player->pos.x = x + 0.5;
	player->pos.y = y + 0.5;
	prm->booleans += START_SET;
	return (0);
}

static int	create_player_dlist(t_param *prm, t_player *player)
{
	if (!(prm->booleans & START_SET))
		return (player_clean_exit(NO_START_POS, player));
	ft_lstadd_back(&(prm->dlist), ft_lstnew(ID_PLAYER, player));
	if (get_lst_elem(prm->dlist, ID_PLAYER) == NULL)
		return (player_clean_exit(MAL_ERR_LIST, player));
	return (0);
}

int			player_init(t_param *prm)
{
	t_player	*player;
	t_map		*map;
	int			ret;
	int			x;
	int			y;

	if (!(player = malloc(sizeof(t_player))))
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
