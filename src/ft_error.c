/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 18:50:26 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/24 15:47:04 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub_macro.h"
#include "ft_utils.h"

static int	arg_error(int err_code)
{
	ft_putstr("ARGUMENT_ERROR : ");
	if (err_code == WRONG_ARG_NUM)
		ft_putstr("Invalid number of arguments\n");
	if (err_code == WRONG_SAVE_STR)
		ft_putstr("Second argument invalid\n");
	if (err_code == WRONG_FILE_EXT)
		ft_putstr("File extension invalid, only .cub and .xpm accepted\n");
	if (err_code == WRONG_FILE_PATH)
		ft_putstr("File doesn't exist\n");
	if (err_code == MISS_CONF_INFO)
		ft_putstr("Configuration informations missing\n");
	return (0);
}

static int	description_error(int err_code)
{
	ft_putstr("DESCRIPTION_ERR : ");
	if (err_code == ID_SPLIT_ERR)
		ft_putstr("Parsing initialisation failed\n");
	if (err_code == NOT_ID_CHAR)
		ft_putstr("First character in line is not an identifier\n");
	if (err_code == WRONG_ID_STR)
		ft_putstr("Invalid line identifier\n");
	if (err_code == NO_MAP_FOUND)
		ft_putstr("No map description found in cub file\n");
	if (err_code == RES_ALRD_SET)
		ft_putstr("Redefinition of res\n");
	if (err_code == TX_ALRD_SET)
		ft_putstr("Redefinition of texture path\n");
	if (err_code == WRONG_RES_ELEM)
		ft_putstr("Invalid number of arguments in resolution line\n");
	if (err_code == WRONG_TX_ELEM)
		ft_putstr("Invalid number of arguments in texture line\n");
	if (err_code == WRONG_TX_PATH)
		ft_putstr("Texture path is invalid\n");
	if (err_code == HCC_ALRD_SET)
		ft_putstr("Redefinition of element color code\n");
	if (err_code == WRONG_HCC_ELEM)
		ft_putstr("Invalid number of arguments in hex color code line\n");
	return (0);
}

static int	map_error(int err_code)
{
	ft_putstr("MAP_ERROR : ");
	if (err_code == MAP_CHAR_INVALID)
		ft_putstr("Invalid character in map description line\n");
	if (err_code == MAP_ALRD_SET)
		ft_putstr("Trying to redefine map grid\n");
	if (err_code == MAP_LEAKS)
		ft_putstr("Map is not closed or contains invalid character\n");
	return (0);
}

static int	malloc_error(int err_code)
{
	ft_putstr("MALLOC_ERROR : ");
	if (err_code == MAL_ERR_PARSE_STRUCT)
		ft_putstr("Parsing structure allocation failed\n");
	if (err_code == MAL_ERR_FILENAME)
		ft_putstr("Error duplicating filename to buffer\n");
	if (err_code == MAL_ERR_DATA)
		ft_putstr("Error allocating data structure\n");
	if (err_code == MAL_ERR_LIST)
		ft_putstr("Error allocating list element\n");
	if (err_code == MAL_ERR_TX_FD)
		ft_putstr("Error creating texture file fd\n");
	if (err_code == MAL_ERR_HCC)
		ft_putstr("Error creating hex color code element\n");
	if (err_code == MAL_ERR_MAP)
		ft_putstr("Error creating map structure\n");
	if (err_code == MAL_ERR_MAP_DUP)
		ft_putstr("Error copiying map line to grid\n");
	if (err_code == MAL_ERR_GRID)
		ft_putstr("Error creating map grid\n");
	return (0);
}

int			ft_error(int err_code)
{
	ft_putstr("Error\n");
	if (err_code >= -10)
		return (arg_error(err_code));
	else if (err_code >= -30)
		return (description_error(err_code));
	else if (err_code >= -40)
		return (map_error(err_code));
	else if (err_code < -40)
		return (malloc_error(err_code));
	return (0);
}
