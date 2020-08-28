/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:12:00 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/28 16:20:11 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
**	DEBUG TOOLS
*/
# include <stdio.h>

//# define malloc($) 0

/*
**	GENERAL INCLUDES
*/
# include "cub_struct.h"

/*
**	MULTI OS SUPPORT
*/
# ifdef Darwin

void			mlx_get_screen_size(void *mlx, int *w, int*h);
#  ifdef bonus
#   define SYS	2
#  else
#   define SYS 	1

int				CGMainDisplayID(void);
int				CGDisplayPixelsWide(int display_id);
int				CGDisplayPixelsHigh(int display_id);
#  endif
# endif

# ifdef Linux

int				CGMainDisplayID(void);
int				CGDisplayPixelsWide(int display_id);
int				CGDisplayPixelsHigh(int display_id);
#  ifdef bonus
#   define SYS	4
#  else
#   define SYS	3
#  endif
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
**	id_filler.c
*/
int				id_hcc_filler(t_param *prm, char **elem, int id);

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
int				ray_caster(t_param *prm);

/*
**	player_init.c
*/
int				player_init(t_param *prm);

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
void			ft_rotate_right(t_param *prm);
void			ft_rotate_left(t_param *prm);

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

#endif
