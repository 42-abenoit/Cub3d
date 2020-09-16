/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 12:33:41 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/16 13:24:58 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub_macro_bonus.h"
#include "ft_utils_bonus.h"

static int	mlx_error(int err_code)
{
	ft_putstr("MLX_ERROR : ");
	if (err_code == MAL_ERR_PARSE_STRUCT)
		ft_putstr("Parsing structure allocation failed\n");
	if (err_code == TX_IMPORT_FAIL)
		ft_putstr("Failed importing textures to mlx.\n");
	if (err_code == MAL_ERR_CONF)
		ft_putstr("Error creating configuration data structure\n");
	if (err_code == MAL_ERR_BUFF)
		ft_putstr("Error creating vertical line buffer\n");
	if (err_code == MAL_ERR_MINIMAP)
		ft_putstr("Error creating minimap configuration structure\n");
	exit(0);
}

int			render_error(int err_code)
{
	if (err_code >= 80)
		return (mlx_error(err_code));
	exit(0);
}