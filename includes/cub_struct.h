/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 13:07:21 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/26 16:58:12 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_STRUCT_H
# define CUB_STRUCT_H

/*
**	STRUCTURES DEFINITIONS
*/
typedef struct	s_parse
{
	int				fd;
	char			*buff;
	char			**id_strings;
}				t_parse;

typedef struct	s_screen
{
	int				width;
	int				height;
}				t_screen;

typedef struct	s_hcc
{
	unsigned int	hcc;
}				t_hcc;

typedef struct	s_coord
{
	double			x;
	double			y;
}				t_coord;

typedef struct	s_map
{
	char			**grid;
	int				size_x;
	int				size_y;
}				t_map;

typedef struct	s_ent
{
	t_coord			pos;
	t_coord			dir;
	double			view_angle;
}				t_ent;

typedef struct	s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}				t_data;

typedef struct	s_tx
{
	t_data			data;
	int				width;
	int				height;
}				t_tx;

typedef struct	s_list
{
	int				type;
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct	s_render
{
	void			*mlx;
	void			*win;
	t_data			*current;
}				t_render;

typedef struct	s_conf
{
	double			front_speed;
	double			back_speed;
	double			strafe_speed;
	double			rot_speed;
}				t_conf;

typedef struct	s_param
{
	unsigned int	booleans;
	void			*ptr;
	t_list			*dlist;
}				t_param;

#endif
