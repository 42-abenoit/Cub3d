/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_macro.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 15:59:55 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/16 16:01:16 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_MACRO_H
# define CUB_MACRO_H

/*
**	MULTI OS SUPPORT MACOS
*/
# ifdef Darwin
#  define INPUT_UP			13
#  define INPUT_DOWN		1
#  define INPUT_LSTRAFE		0
#  define INPUT_RSTRAFE		2
#  define INPUT_LEFT		123
#  define INPUT_RIGHT		124
#  define INPUT_ESC			53
# endif

/*
**	MULTI OS SUPPORT LINUX
*/
# ifdef Linux
#  ifdef keyboard_fr
#   define INPUT_UP			122
#   define INPUT_DOWN		115
#   define INPUT_LSTRAFE		113
#   define INPUT_RSTRAFE		100
#   define INPUT_LEFT		65361
#   define INPUT_RIGHT		65363
#   define INPUT_ESC			65307
#  else
#   define INPUT_UP			119
#   define INPUT_DOWN		115
#   define INPUT_LSTRAFE		97
#   define INPUT_RSTRAFE		100
#   define INPUT_LEFT		65361
#   define INPUT_RIGHT		65363
#   define INPUT_ESC			65307
#  endif
# endif

/*
**	ERR_CODE DEFINITIONS
*/
# define WRONG_ARG_NUM 			-1
# define WRONG_SAVE_STR 		-2
# define WRONG_FILE_EXT 		-3
# define WRONG_FILE_PATH 		-4
# define MISS_CONF_INFO			-5
# define ID_SPLIT_ERR			-6
# define NOT_ID_CHAR 			-7
# define WRONG_ID_STR 			-8
# define NO_MAP_FOUND 			-9

# define RES_ALRD_SET			-11
# define TX_ALRD_SET			-12
# define WRONG_RES_ELEM			-13
# define WRONG_RES_CHAR			-14
# define WRONG_TX_ELEM			-15
# define WRONG_TX_PATH			-16
# define HCC_ALRD_SET			-17
# define WRONG_HCC_ELEM			-18
# define WRONG_HCC_CHAR			-19
# define WRONG_HCC_VAL			-20
# define CONF_AFTER_MAP			-21

# define MAP_CHAR_INVALID		-31
# define MAP_ALRD_SET			-32
# define MAP_LEAKS				-33
# define START_ALRD_SET			-34
# define NO_START_POS			-35

# define MAL_ERR_PARSE_STRUCT 	-41
# define MAL_ERR_FILENAME 		-42
# define MAL_ERR_SCREEN	 		-43
# define MAL_ERR_LIST	 		-44
# define MAL_ERR_TX_PATH 		-45
# define MAL_ERR_HCC	 		-46
# define MAL_ERR_MAP	 		-47
# define MAL_ERR_MAP_DUP		-48
# define MAL_ERR_GRID			-49
# define MAL_ERR_PLAYER			-50
# define MAL_ERR_RENDER			-51

# define MLX_INIT_FAIL			-61
# define TX_IMPORT_FAIL			-62
# define MAL_ERR_CONF			-63
# define MAL_ERR_BUFF			-64

/*
**	IMPORTANT CHARSETS AND STRINGS
*/
# define BASE_10				"0123456789"
# define SAVE_STR				"--save"
# define CUB_EXT				".cub"
# define XPM_EXT				".xpm"
# define WHITESPACES			"\t\n\v\f\r' '"

/*
**	PARSING IDENTIFIERS
*/
# define IS_ID					"RNSWEFC"
# define ID_STRINGS				"R/NO/SO/WE/EA/S/F/C"

/*
**	DLIST IDENTIFIERS
*/
# define ID_RES					0
# define ID_TX_NO				1
# define ID_TX_SO				2
# define ID_TX_WE				3
# define ID_TX_EA				4
# define ID_TX_S				5
# define ID_HCC_F				6
# define ID_HCC_C				7
# define ID_MAP					8
# define ID_PLAYER				9
# define ID_CONF				10

/*
**	MAP IDENTIFIERS
*/
# define MAP_VALID_CHAR			"012NSWE' '"
# define MAP_EMPTY				" "
# define MAP_OBSTACLE			"12"
# define MAP_PLAY_AREA			"02NSWE"
# define MAP_WALKABLE			"0NSWE"
# define MAP_START				"NSWE"

/*
**	BOOLEANS BITS MASKS
*/
# define BMP_SAVE				0x00000001
# define RES_SET				0x00000002
# define TX_NO_SET				0x00000004
# define TX_SO_SET				0x00000008
# define TX_WE_SET				0x00000010
# define TX_EA_SET				0x00000020
# define TX_S_SET				0x00000040
# define HCC_F_SET				0x00000080
# define HCC_C_SET				0x00000100
# define MAP_SET				0x00000200
# define START_SET				0x00000400
# define START_RENDER			0x00000800
# define TX_IMPORT				0x00001000

# define FLAG_UP				0x00002000
# define FLAG_DOWN				0x00004000
# define FLAG_LSTRAFE			0x00008000
# define FLAG_RSTRAFE			0x00010000
# define FLAG_LEFT				0x00020000
# define FLAG_RIGHT				0x00040000
# define FLAG_MAP				0x00080000
# define FLAG_AXE				0x00100000
# define FLAG_JUMP				0x00200000

# define IMG_SET				0x10000000

# define CONF_SET				0x000003FE
# define PARSE_END				0x00000FFF

#endif
