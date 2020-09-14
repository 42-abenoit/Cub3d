/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 13:07:21 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/14 12:20:36 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_STRUCT_H
# define CUB_STRUCT_H

/*
**	PLAYER STATE ENUM
*/
typedef enum	e_state
{
	IDLE,
	AXE,
	ANIM1,
	ANIM2,
	MAP
}				t_state;

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

typedef struct	s_int_coord
{
	int				x;
	int				y;
}				t_int_coord;

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

typedef struct	s_player
{
	t_coord			pos;
	t_coord			dir;
	t_coord			plane;
	double			view_angle;
	double			pos_z;
	double			pitch;
	char			jump_phase;
	char			jump_max;
	char			anim_phase;
	t_state			state;
}				t_player;

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

typedef struct	s_sprite
{
	t_coord			pos;
	t_coord			sprite;
	t_coord			transform;
	t_int_coord		draw_start;
	t_int_coord		draw_end;
	t_int_coord		tex;
	int				type;
	int				hp;
	int				sprite_screen_x;
	int				sprite_width;
	int				sprite_height;
	int				v_move_screen;
	char			hit;
	double			dist;
	double			inv_det;
	struct s_sprite	*next;
	struct s_sprite	*prev;
}				t_sprite;

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
	double			frame_time;
	t_data			img;
	t_data			current;
}				t_render;

typedef struct	s_conf
{
	double			pitch_sensi;
	double			jump_height;
	int				fog_color;
	double			view_depth;
	double			front_speed;
	double			back_speed;
	double			strafe_speed;
	double			rot_speed;
}				t_conf;

typedef struct	s_miniconf
{
	t_coord		map_ratio;
	t_coord		ratio;
	t_coord		persp;
	t_coord		step;
	t_coord		size;
	t_int_coord	mini;
	int			offset_x;
}				t_miniconf;

typedef struct	s_ray
{
	t_coord			dir;
	t_coord			side_dist;
	t_coord			delta_dist;
	t_int_coord		map;
	t_int_coord		pos;
	t_int_coord		tex;
	t_int_coord		step;
	t_int_coord		side;
	t_tx			*tx_ptr;
	double			camera_x;
	double			perp_wall_dist;
	double			dist;
	double			wall_x;
	double			tex_step;
	double			tex_pos;
	int				*line_buff;
	int				horizon;
	int				hit;
	int				color;
	int				id_side;
	int				line_height;
	int				draw_start;
	int				draw_end;
}				t_ray;

typedef struct	s_floor
{
	t_tx			*tx_ptr;
	t_coord			wall;
	t_coord			current;
	t_int_coord		tex;
	double			dist_wall;
	double			dist_player;
	double			current_dist;
	double			weight;
	char			is_floor;
}				t_floor;

typedef struct	s_param
{
	unsigned int	booleans;
	unsigned int	flags;
	void			*ptr;
	t_list			*dlist;
}				t_param;

typedef struct	s_thread
{
	int				id_thread;
	t_param			*prm;
}				t_thread;

#endif
