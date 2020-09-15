/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:12:00 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/15 11:58:14 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
**	DEBUG TOOLS
**
**	# define malloc($) 0
**	# include <stdio.h>
*/

/*
**	GENERAL INCLUDES
*/
# include "cub_struct.h"

/*
**	MULTI OS SUPPORT
*/
# ifdef Darwin
#  define SYS 	1

int				CGMainDisplayID(void);
int				CGDisplayPixelsWide(int display_id);
int				CGDisplayPixelsHigh(int display_id);
void			mlx_get_screen_size(void *mlx, int *w, int*h);
# endif

# ifdef Linux
#  define SYS	2

int				CGMainDisplayID(void);
int				CGDisplayPixelsWide(int display_id);
int				CGDisplayPixelsHigh(int display_id);
# endif

/*
**	parse_trigger.c
*/
int				parse_trigger(t_param *prm);

/*
**	parse_line.c
*/
int				parse_line(t_param *prm);

/*
**	id_filler.c
*/
int				id_res_filler(t_param *prm, char **elem);
int				id_path_filler(t_param *prm, char **elem, int id);

/*
**	parse_map.c
*/
int				parse_map(t_param *prm);

/*
**	control_map.c
*/
int				control_map(t_param *prm);

/*
**	game_struct.c
*/
int				game_struct_init(t_param *prm);

/*
**	render_engine.c
*/
void			ray_init(int x, t_ray *ray, t_param *prm);
int				ray_caster(t_param *prm);

/*
**	render_engine_ray.c
*/
void			ray_hit_scan(t_ray *ray, t_param *prm);
void			ray_perspective(t_ray *ray, t_param *prm);
void			ray_texture(t_ray *ray, t_param *prm);

/*
**	render_engine_ray.c
*/
void			img_refresh(t_param *prm);
void			fill_buffer(int x, t_ray *ray, t_param *prm);

/*
**	sprites.c
*/
void			sprite_calc_dist(t_param *prm);
void			sprite_projection(t_param *prm);
void			ray_fill_line_sprite(int x, t_ray *ray, t_param *prm);

/*
**	floor.c
*/
void			floor_init(t_floor *floor, t_ray *ray);
void			ray_fill_line_floor(int x, t_floor *floor, t_ray *ray, t_param *prm);

/*
**	sky.c
*/
void			fill_sky_line(int x, t_ray *ray, t_param *prm);

/*
**	sfx.c
*/
int				apply_fog(double dist, int color_input, t_param *prm);
int				apply_hit_effect(int color_input);

/*
**	player_char.c
*/
void			player_to_screen(int x, t_ray *ray, t_param *prm);
void			ft_player_state(t_param *prm);

/*
**	minimap.c
*/
int				minimap_init(t_param *prm);
void			minimap_to_screen(int x, t_ray *ray, t_param *prm);

/*
**	player_init.c
*/
int				player_init(t_param *prm);

/*
**	sprites_init.c
*/
int				sprite_init(t_param *prm);

/*
**	bmp_save.c
*/
int				pic_calculate(t_param *prm);

/*
**	bmp_export.c
*/
void			pic_export(t_param *prm, t_screen *screen);

/*
**	manage_key.c
*/
int				ft_key_press(int keycode, t_param *prm);
int				ft_key_release(int keycode, t_param *prm);
int				ft_move(t_param *prm);

/*
**	move_set.c
*/
void			ft_forward(t_param *prm);
void			ft_backward(t_param *prm);
void			ft_strafe_left(t_param *prm);
void			ft_strafe_right(t_param *prm);

/*
**	move_set_2.c
*/
void			ft_look_up(t_param *prm);
void			ft_look_down(t_param *prm);
void			ft_rotate_right(t_param *prm);
void			ft_rotate_left(t_param *prm);

/*
**	move_set_3.c
*/
void			ft_sneak(t_param *prm);
void			ft_sprint(t_param *prm);
void			ft_reset_conf(t_param *prm);

/*
**	move_set_4.c
*/
void			ft_jump(t_param *prm);

/*
**	move_valid.c
*/
void			move_valid(t_param *prm, t_coord new_pos);

/*
**	ft_error.c
*/
int				ft_error(int err_code);

/*
**	ft_error_2.c
*/
int				render_error(int err_code);

/*
**	ft_exit.c
*/
int				clean_parse(t_param *prm);
int				clean_render(t_param *prm);
int				ft_exit(int err_code, t_param *prm);
int				ui_cross_exit(t_param *prm);

#endif
