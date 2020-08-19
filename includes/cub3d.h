/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:12:00 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/19 18:43:56 by abenoit          ###   ########.fr       */
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
**	ERR_CODE DEFINITIONS
*/
# define WRONG_ARG_NUM 			-1
# define WRONG_SAVE_STR 		-2
# define WRONG_FILE_EXT 		-3
# define WRONG_FILE_PATH 		-4

# define ID_SPLIT_ERR			-11
# define NOT_ID_CHAR 			-12
# define WRONG_ID_STR 			-13
# define NO_MAP_FOUND 			-14
# define WRONG_RES_ELEM			-15

# define MAL_ERR_PARSE_STRUCT 	-31
# define MAL_ERR_FILENAME 		-32

/*
**	IMPORTANT CHARSETS AND STRINGS
*/
# define BASE_10				"0123456789"
# define SAVE_STR				"--save"
# define VALID_EXT				".cub"
# define WHITESPACES			"\t\n\v\f\r' '"

/*
**	IDENTIFIERS VERIFICATION
*/
# define IS_ID					"RNSWEFC"
# define ID_STRINGS				"R/NO/SO/WE/EA/S/F/C"
# define ID_RES					0
# define ID_TEX_NORTH			1
# define ID_TEX_SOUTH			2
# define ID_TEX_WEST			3
# define ID_TEX_EAST			4
# define ID_TEX_SPRITE			5
# define ID_COLOR_FLOOR			6
# define ID_COLOR_CEIL			7

/*
**	MAP CHARACTER SET
*/
# define VALID_MAP				"012NSWE"

/*
**	BOOLEANS BITS MASKS
*/
# define BMP_SAVE				0x000000001

/*
**	STRUCTURES DEFINITIONS
*/

typedef struct	s_parse
{
	int				fd;
	char			*buff;
	char			**id_strings;
}				t_parse;

typedef struct	s_tx
{
	int				id;
	void			*path;
}				t_tx;

typedef struct	s_hcc
{
	int				id;
	unsigned int	hcc;
}				t_hcc;

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct	s_param
{
	unsigned int	booleans;
	void			*ptr;
	int				img_width;
	int				img_height;
	t_list			*list;
}				t_param;

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
int				id_res_filler(char **elem);


/*
**	ft_error.c
*/
int				ft_error(int err_code);

/*
**	ft_exit.c
*/
int				ft_exit(int err_code, t_param *prm);

#endif
