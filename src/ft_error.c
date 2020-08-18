/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 18:50:26 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/18 21:25:22 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_utils.h"

static int	arg_error(int err_code)
{
	ft_putstr("ARGUMENT_ERROR : ");
	if (err_code == WRONG_ARG_NUM)
		ft_putstr("Invalid number of arguments\n");
	if (err_code == WRONG_SAVE_STR)
		ft_putstr("Second argument invalid\n");
	if (err_code == WRONG_FILE_EXT)
		ft_putstr("File extension invalid\n");
	if (err_code == WRONG_FILE_PATH)
		ft_putstr("File doesn't exist\n");
	return (0);
}

static int	description_error(int err_code)
{
	ft_putstr("DESCRIPTION_ERROR : ");
	if (err_code == WRONG_ID_CHAR)
		ft_putstr("Invalid character in cub file\n");
	if (err_code == NO_MAP_FOUND)
		ft_putstr("No map description found in cub file\n");
	return (0);
}

static int	malloc_error(int err_code)
{
	ft_putstr("MALLOC_ERROR : ");
	if (err_code == MAL_ERR_PARSE_STRUCT)
		ft_putstr("Parsing structure allocation failed\n");
	if (err_code == MAL_ERR_FILENAME)
		ft_putstr("Error duplicating filename to buffer\n");
	return (0);
}

int			ft_error(int err_code)
{
	ft_putstr("Error\n");
	if (err_code >= -10)
		return (arg_error(err_code));
	if (err_code >= -20)
		return (description_error(err_code));
	if (err_code < -30)
		return (malloc_error(err_code));
	return (0);
}
