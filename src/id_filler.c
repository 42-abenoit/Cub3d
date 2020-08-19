/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_filler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 17:48:41 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/19 18:22:10 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_utils.h"

static int	elem_count(char **elem)
{
	int		i;

	i = 0;
	while (elem[i] != NULL)
		i++;
	return (i);
}

int			id_res_filler(char **elem)
{
	int	tmp;

	if (elem_count(elem) != 3)
		return (WRONG_RES_ELEM);
	tmp = ft_atoi_base(elem[1], BASE_10);
	printf("res_x = %d\n", tmp);
	tmp = ft_atoi_base(elem[2], BASE_10);
	printf("res_y = %d\n", tmp);
	return (0);
}
