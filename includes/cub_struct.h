/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 13:07:21 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/24 10:58:35 by abenoit          ###   ########.fr       */
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

typedef struct	s_data
{
	int				width;
	int				height;
}				t_data;

typedef struct	s_fd
{
	int				fd;
}				t_fd;

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
	t_coord			plane;
}				t_ent;

typedef struct	s_list
{
	int				type;
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct	s_param
{
	unsigned int	booleans;
	void			*ptr;
	t_list			*dlist;
}				t_param;

#endif
