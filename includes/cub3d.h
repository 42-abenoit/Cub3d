/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:12:00 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/18 21:27:52 by abenoit          ###   ########.fr       */
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

# define WRONG_ID_CHAR 			-11
# define NO_MAP_FOUND 			-12

# define MAL_ERR_PARSE_STRUCT 	-31
# define MAL_ERR_FILENAME 		-32

/*
**	IMPORTANT CHARSETS AND STRINGS
*/
# define SAVE_STR "--save"
# define VALID_EXT ".cub"
# define WHITESPACES "\t\n\v\f\r' '"

/*
**	IDENTIFIERS VERIFICATION
*/
# define IS_ID "RNSWEFC"
# define ID_RES "R"
# define ID_NORTH_TEX "NO"
# define ID_SOUTH_TEX "SO"
# define ID_WEST_TEX "WE"
# define ID_EAST_TEX "EA"
# define ID_SPRITE_TEX "S"
# define ID_FLOOR_COLOR "F"
# define ID_CEIL_COLOR "C"

/*
**	MAP CHARACTER SET
*/
# define VALID_MAP "012NSWE"

/*
**	BOOLEANS BITS MASKS
*/
# define BMP_SAVE 0x000000001

/*
**	STRUCTURES DEFINITIONS
*/

typedef struct	s_parse
{
	int				fd;
	char			*buff;
}				t_parse;

typedef struct	s_param
{
	unsigned int	booleans;
	void			*ptr;
}				t_param;

/*
**	parse_trigger.c
*/
int				parse_trigger(t_param *prm);

/*
**	ft_error.c
*/
int				ft_error(int err_code);

/*
**	ft_exit.c
*/
int				ft_exit(int err_code, t_param *prm);

#endif
