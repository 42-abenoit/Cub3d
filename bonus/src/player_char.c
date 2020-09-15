/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 11:49:23 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/15 16:00:52 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "cub3d.h"
#include "ft_utils.h"
#include "cub_macro.h"
#include "cub_struct.h"

void	player_to_screen(int x, t_ray *ray, t_param *prm)
{
	t_coord		ratio;
	int			y;
	t_cfp		cfp;
	const char	tx_id[] = {0, ID_TX_CA, ID_TX_CA1, ID_TX_CA2, ID_TX_CM};

	cfp.player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	if (cfp.player->state == IDLE)
		return ;
	cfp.render = prm->ptr;
	cfp.tx = get_lst_elem(prm->dlist, tx_id[cfp.player->state])->content;
	cfp.screen = get_lst_elem(prm->dlist, ID_RES)->content;
	ratio.x = ((double)cfp.tx->width) / ((double)cfp.screen->width);
	ratio.y = ((double)cfp.tx->height) / ((double)cfp.screen->height);
	y = 0;
	while (y < cfp.screen->height)
	{
		ray->color = get_pixel_color(x * ratio.x, y * ratio.y, &cfp.tx->data);
		if ((ray->color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(&cfp.render->img, x, y, ray->color);
		y++;
	}
	if (cfp.player->state == MAP)
		minimap_to_screen(x, prm);
}

void	ft_player_state(t_param *prm)
{
	t_player	*player;

	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	if (player->anim_phase > 0)
	{
		if (player->anim_phase < 10)
			ft_axe_phase(prm);
		else
			ft_map_phase(prm);
	}
	else if (prm->flags & FLAG_STRIKE)
		player->anim_phase = 1;
	else if (prm->flags & FLAG_AXE)
		player->state = AXE;
	else if (prm->flags & FLAG_MAP)
		player->anim_phase = 11;
	else
		player->state = IDLE;
}
