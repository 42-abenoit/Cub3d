/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 23:35:36 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/11 12:36:22 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static int	minimap_clean_exit(int ret, t_tx *tx, t_minimap *miniconf)
{
	if (tx != NULL)
		free(tx);
	tx = NULL;
	if (miniconf != NULL)
		free(miniconf);
	miniconf = NULL;
	return (ret);
}

int			minimap_init(t_param *prm)
{
	int			ret;
	t_map		*map
	t_screen	*screen;
	t_render	*render;
	t_miniconf	*miniconf;
	t_tx		*tx;

	
	map = get_lst_elem(prm->dlist, ID_MAP)->content;
	screen = get_lst_elem(prm->dlist, ID_SCREEN)->content;
	render = prm->ptr;
	if (!(tx = malloc(sizeof(t_tx))))
		return (MAL_ERR_MINIMAP);
	if (!(miniconf = malloc(sizeof(t_miniconf))))
		return (minimap_clean_exit(MAL_ERR_LIST, tx, minimap));
	tx->size_x = (int)((double)screen->width / 1.5);
	tx->size_y = (int)((double)screen->height / 1.5);
	tx->data.img = mlx_new_image(prm->mlx, tx->size.x,tx->size.y);
	tx->data.addr = mlx_get_data_addr(tx->data.img,
						&(tx->data.bits_per_pixel),
						&(tx->data.line_length),
						&(tx->data.endian));
	ft_lstadd_back(&(prm->dlist), ft_lstnew(ID_MINIMAP, tx));
	if (get_lst_elem(prm->dlist, ID_MINIMAP) == NULL)
		return (minimap_clean_exit(MAL_ERR_LIST, tx, minimap));

	miniconf->persp.x = 0.60;
	miniconf->persp.y = 0.90;
	miniconf->ratio_x = (double)screen->width / (double)tx->size.x;
	miniconf->ratio_y = (double)screen->height / (double)tx->size.y;
	miniconf->map.x = (double)tx->size.x / (double)map->size_x; 
	miniconf->map.y = (double)tx->size.y / (double)map->size_y;
	miniconf->step.x = (0.4 / (double)miniconf->size.y);
	miniconf->step.y = (0.10 / (double)miniconf->size.y);
	ft_lstadd_back(&(prm->dlist), ft_lstnew(ID_MINICONF, miniconf));
	if (get_lst_elem(prm->dlist, ID_MINICONF) == NULL)
		return (minimap_clean_exit(MAL_ERR_LIST, tx, minimap));
	return (0);
}

void	minimap_draw(int x, t_ray *ray, t_param *prm)
{
	int			y;
	t_tx		*tx;
	t_player	*player;
	t_miniconf	*miniconf;

	mini_y = 0;
	tx = get_lst_elem(prm->dlist, ID_MINIMAP)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	miniconf = get_lst_elem(prm->dlist, ID_MINICONF)->content;
	while (mini_y < bonus->minimap_size_y)
	{
		y = (int)floor((double)mini_y / map_y);
		mini_x = 0;
		offset_x = ((double)bonus->minimap_size_x / 2.0) * (1.0 - ratio_x);
		while (mini_x < bonus->minimap_size_x)
		{
			x = (int)floor((double)mini_x / map_x);
			if (mini_x <= offset_x)
			{
				my_mlx_pixel_put(&bonus->minimap, mini_x, (int)((double)mini_y), 0x00F0DEB1);
				my_mlx_pixel_put(&bonus->minimap, bonus->minimap_size_x - 1 - mini_x, (int)((double)mini_y), 0x00F0DEB1);
			}
			if ((x >= 0 && x <= prm->map_x_size) && (y >= 0 && y <= prm->map_y_size))
			{
			if (prm->map[y][x] == '1')
				color = 0x00909090;
			else if (prm->map[y][x] == '2')
				color = 0x00FAFFFA;
			else if (y == floor(prm->start.y) && x == floor(prm->start.x))
				color = 0x0000FFFF;
			else
				color = 0xFF010101;
			if ((color & 0x00FFFFF) != 0)
				my_mlx_pixel_put(&bonus->minimap, offset_x + (int)(ratio_x * (double)mini_x), (int)((double)mini_y), color);
			}
			mini_x++;
		}
		mini_y++;
		ratio_x += step_x;
	}
}
