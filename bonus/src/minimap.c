/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 23:35:36 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/11 15:50:18 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "mlx.h"
#include "cub3d.h"
#include "ft_utils.h"
#include "cub_struct.h"
#include "cub_macro.h"

static int	minimap_clean_exit(int ret, t_tx *tx, t_miniconf *miniconf)
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
	t_map		*map;
	t_screen	*screen;
	t_render	*render;
	t_miniconf	*miniconf;
	t_tx		*tx;

	
	map = get_lst_elem(prm->dlist, ID_MAP)->content;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	render = prm->ptr;
	if (!(tx = malloc(sizeof(t_tx))))
		return (MAL_ERR_MINIMAP);
	if (!(miniconf = malloc(sizeof(t_miniconf))))
		return (minimap_clean_exit(MAL_ERR_MINICONF, tx, miniconf));
	tx->width = (int)((double)screen->width / 1.5);
	tx->height = (int)((double)screen->height / 1.5);
	tx->data = my_mlx_new_image(render->mlx, tx->width,tx->height);
	ft_lstadd_back(&(prm->dlist), ft_lstnew(ID_MINIMAP, tx));
	if (get_lst_elem(prm->dlist, ID_MINIMAP) == NULL)
		return (minimap_clean_exit(MAL_ERR_LIST, tx, miniconf));

	miniconf->ratio.x = (double)screen->width / (double)tx->width;
	miniconf->ratio.y = (double)screen->height / (double)tx->height;
	miniconf->map.x = (double)tx->width / (double)map->size_x; 
	miniconf->map.y = (double)tx->height / (double)map->size_y;
	miniconf->step.x = (0.25 / (double)tx->height);
	miniconf->step.y = (0.10 / (double)tx->height);
	ft_lstadd_back(&(prm->dlist), ft_lstnew(ID_MINICONF, miniconf));
	if (get_lst_elem(prm->dlist, ID_MINICONF) == NULL)
		return (minimap_clean_exit(MAL_ERR_LIST, tx, miniconf));
	return (0);
}

void	create_minimap(t_param *prm)
{
	int			y;
	int			x;
	int			color;
	t_tx		*tx;
	t_map		*map;
	t_player	*player;
	t_miniconf	*miniconf;

	tx = get_lst_elem(prm->dlist, ID_MINIMAP)->content;
	map	= get_lst_elem(prm->dlist, ID_MAP)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	miniconf = get_lst_elem(prm->dlist, ID_MINICONF)->content;
	miniconf->mini.y = 0;
	miniconf->persp.x = 0.75;
	miniconf->persp.y = 0.90;
	while (miniconf->mini.y < tx->height - 1)
	{
		color = 0;
		y = (int)floor((double)miniconf->mini.y / miniconf->map.y);
		miniconf->mini.x = 0;
		miniconf->offset_x = ((double)tx->width / 2.0) * (1.0 - miniconf->persp.x);
		while (miniconf->mini.x < tx->width - 1)
		{
			x = (int)floor((double)miniconf->mini.x / miniconf->map.x);
			if (miniconf->mini.x <= miniconf->offset_x)
			{
				my_mlx_pixel_put(&tx->data, miniconf->mini.x, (int)((double)miniconf->mini.y), 0x00F0DEB1);
				my_mlx_pixel_put(&tx->data, tx->width - 1 - miniconf->mini.x, (int)((double)miniconf->mini.y), 0x00F0DEB1);
			}
			if ((y >= 0 && y < map->size_y) && (x >= 0 && x <= ft_strlen(map->grid[y])))
			{
			if (map->grid[y][x] == '1')
				color = 0x00909090;
			else if (map->grid[y][x] == '2')
				color = 0x00FAFFFA;
			else if (y == floor(player->pos.y) && x == floor(player->pos.x))
				color = 0x0000FFFF;
			else
				color = 0x00F0DEB1;
			my_mlx_pixel_put(&tx->data, miniconf->offset_x + (int)(miniconf->persp.x * (double)miniconf->mini.x), (int)((double)miniconf->mini.y), color);
			}
			miniconf->mini.x++;
		}
		miniconf->mini.y++;
		miniconf->persp.x += miniconf->step.x;
	}
}

void	minimap_to_screen(int x, t_ray *ray, t_param *prm)
{
	int			y;
	int			start_x;
	int			start_y;
	t_tx		*tx;
	t_screen	*screen;
	t_miniconf	*miniconf;

	tx = get_lst_elem(prm->dlist, ID_MINIMAP)->content;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	miniconf = get_lst_elem(prm->dlist, ID_MINICONF)->content;
	start_x = (screen->width / miniconf->ratio.x) / 4;
	start_y = (screen->height / miniconf->ratio.y) / 3;
	y = start_y;
	if (x < start_x || x > start_x + tx->width - 1)
		return ;
	while (y < start_y + tx->height - 1)
	{
		ray->color = get_pixel_color(((x - start_x) * miniconf->ratio.x / 1.5), ((y - start_y) * miniconf->ratio.y / 1.5), &tx->data);
		if ((ray->color & 0x00FFFFFF) != 0)
			ray->line_buff[y] = ray->color;
		y++;
	}
}
