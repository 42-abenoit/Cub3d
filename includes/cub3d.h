/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:12:00 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/24 20:24:29 by abenoit          ###   ########.fr       */
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
int				id_fd_filler(t_param *prm, char **elem, int id);

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
**	player_init.c
*/
int				player_init(t_param *prm);

/*
**	ft_error.c
*/
int				ft_error(int err_code);

/*
**	ft_exit.c
*/
int				clean_parse(t_param *prm);
int				clean_render(t_param *prm);
int				ft_exit(int err_code, t_param *prm);

#endif
