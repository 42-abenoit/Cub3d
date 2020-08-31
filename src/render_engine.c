/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_engine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 16:16:35 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/31 16:52:30 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "cub3d.h"
#include "ft_utils.h"
#include "cub_macro.h"
#include "cub_struct.h"

void		ray_init(int x, t_ray *ray, t_param *prm)
{
	t_screen	*screen;
	t_player	*player;

	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	ray->camera_x = 2 * x / (double)screen->width - 1;
	ray->dir.x = player->dir.x + player->plane.x * ray->camera_x;
	ray->dir.y = player->dir.y + player->plane.y * ray->camera_x;
	ray->map.x = (int)player->pos.x;
	ray->map.y = (int)player->pos.y;
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
	ray->hit = 0;
	ray->sprites = NULL;
}

static void		img_refresh(t_ray *ray, t_param *prm)
{
	t_render	*render;

	render = prm->ptr;
	if (prm->booleans & IMG_SET)
	{
		mlx_destroy_image(render->mlx, render->current.img);
		render->current.addr = NULL;
	}
	else
		prm->booleans += IMG_SET;
	free(ray->line_buff);
	render->current = ray->img;
	mlx_put_image_to_window(render->mlx, render->win,
							render->current.img, 0, 0);
}

void			ray_step(t_ray *ray, t_param *prm)
{
	t_player	*player;

	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (player->pos.x - ray->map.x) * ray->delta_dist.x;
		ray->side.x = 0;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - player->pos.x) * ray->delta_dist.x;
		ray->side.x = 2;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (player->pos.y - ray->map.y) * ray->delta_dist.y;
		ray->side.y = 1;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - player->pos.y) * ray->delta_dist.y;
		ray->side.y = 3;
	}
}

void	ray_hit_scan(t_ray *ray, t_param *prm)
{
	t_player	*player;
	t_map		*map;
	t_sprite	*new;

	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	map = get_lst_elem(prm->dlist, ID_MAP)->content;
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->id_side = ray->side.x;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->id_side = ray->side.y;
		}
		if (map->grid[ray->map.y][ray->map.x] == '1')
			ray->hit = 1;
		else if (map->grid[ray->map.y][ray->map.x] == '2')
		{
			new = ft_new_sprite(ray->map.x, ray->map.y);
			new->dist = ((player->pos.x - new->pos.x) * (player->pos.x - new->pos.x)
					+ (player->pos.y - new->pos.y) * (player->pos.y - new->pos.y));
			ft_add_sprite_front(&ray->sprites, new);
		}
	}
}

void	ray_perspective(t_ray *ray, t_param *prm)
{
	t_player	*player;
	t_screen	*screen;

	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	if (ray->id_side % 2 == 0)
		ray->perp_wall_dist = (ray->map.x - player->pos.x + (1 - ray->step.x) / 2)
							/ ray->dir.x;
	else
		ray->perp_wall_dist = (ray->map.y - player->pos.y + (1 - ray->step.y) / 2)
							/ ray->dir.y;
	ray->line_height = (int)(screen->height / ray->perp_wall_dist);
	ray->draw_start = (-ray->line_height / 2) + (screen->height / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2) + (screen->height / 2);
	if (ray->draw_end >= screen->height)
		ray->draw_end = screen->height - 1;
}

void	ray_texture(t_ray *ray, t_param *prm)
{
	t_player	*player;
	t_screen	*screen;

	player = get_lst_elem(prm->dlist, ID_PLAYER)->content;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	if (ray->id_side == 0)
		ray->tx_ptr = get_lst_elem(prm->dlist, ID_TX_WE)->content;
	else if (ray->id_side == 1)
		ray->tx_ptr = get_lst_elem(prm->dlist, ID_TX_NO)->content;
	else if (ray->id_side == 2)
		ray->tx_ptr = get_lst_elem(prm->dlist, ID_TX_EA)->content;
	else if (ray->id_side == 3)
		ray->tx_ptr = get_lst_elem(prm->dlist, ID_TX_SO)->content;
	if (ray->id_side % 2 == 0)
		ray->wall_x = player->pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		ray->wall_x = player->pos.x + ray->perp_wall_dist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex.x = (int)(ray->wall_x * (double)(ray->tx_ptr->width));
	if ((ray->id_side % 2 == 0) && ray->dir.x > 0)
		ray->tex.x = ray->tx_ptr->width - ray->tex.x - 1;
	if (ray->id_side % 2 == 1 && ray->dir.y < 0)
		ray->tex.x = ray->tx_ptr->width - ray->tex.x - 1;
	ray->tex_step = 1.0 * ray->tx_ptr->height / ray->line_height;
	ray->tex_pos = (ray->draw_start - screen->height / 2 + ray->line_height / 2)
					* ray->tex_step;
}

void			fill_buffer(t_ray *ray, t_param *prm)
{
	int			y;
	t_hcc		*hcc;
	t_screen	*screen;

	y = 0;	
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	hcc = get_lst_elem(prm->dlist, ID_HCC_C)->content;
	while (y < ray->draw_start)
	{
		ray->line_buff[y] = hcc->hcc;
		y++;
	}
	while (y < ray->draw_end)
	{
		ray->tex.y = (int)ray->tex_pos & (ray->tx_ptr->height - 1);
		ray->tex_pos += ray->tex_step;
		ray->color = get_pixel_color(ray->tex.x, ray->tex.y, &ray->tx_ptr->data);
		ray->line_buff[y] = ray->color;
		y++;
	}
	hcc = get_lst_elem(prm->dlist, ID_HCC_F)->content;
	while (y < screen->height - 1)
	{
		ray->line_buff[y] = hcc->hcc;
		y++;
	}
}

void			fill_line(int x, t_ray *ray, t_param *prm)
{
	int			y;
	t_screen	*screen;

	y = 0;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	while (y < screen->height - 1)
	{
		my_mlx_pixel_put(&ray->img, x, y, ray->line_buff[y]);
		y++;
	}
}

int				ray_caster(t_param *prm)
{
	t_ray		ray;
	t_screen	*screen;
	t_render	*render;
	int			x;

	x = 0;
	render = prm->ptr;
	screen = get_lst_elem(prm->dlist, ID_RES)->content;
	ray.img = my_mlx_new_image(render->mlx, screen->width, screen->height);
	if (!(ray.line_buff = malloc(screen->height * sizeof(int))))
		return (MAL_ERR_BUFF);
	while (x < screen->width)
	{
		ray_init(x, &ray, prm);
		ray_step(&ray, prm);
		ray_hit_scan(&ray, prm);
		ray_perspective(&ray, prm);
		ray_texture(&ray, prm);
		fill_buffer(&ray, prm);
		sprite_projection(&ray, prm);
		ray_fill_line_sprite(x, &ray, prm);
		fill_line(x, &ray, prm);
		ft_clear_list(&ray.sprites);
		x++;
	}
	img_refresh(&ray, prm);
	ft_move(prm);
	return (0);
}
