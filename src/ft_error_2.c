/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 12:33:41 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/26 12:38:19 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_macro.h"
#include "ft_utils.h"

static int	mlx_error(int err_code)
{
	ft_putstr("MALLOC_ERROR : ");
	if (err_code == MAL_ERR_PARSE_STRUCT)
		ft_putstr("Parsing structure allocation failed\n");
	return (0);
}

int			render_error(int err_code)
{
	if (err_code >= 80)
		return (mlx_error(err_code));
	return (0);
}
