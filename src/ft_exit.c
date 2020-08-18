/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 20:13:48 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/18 20:24:30 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"

int		ft_exit(int err_code, t_param *prm)
{
	free(((t_parse*)(prm->ptr))->buff);
	free(prm->ptr);
	if (err_code == 0)
		return (0);
	else
		return (ft_error(err_code));
}
