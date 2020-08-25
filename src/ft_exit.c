/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 20:13:48 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/25 11:31:51 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"
#include "ft_utils.h"

int		ft_exit(int err_code, t_param *prm)
{
	t_parse		*tmp;
	int			i;

	if (prm->ptr != NULL)
	{
		tmp = ((t_parse*)(prm->ptr));
		if (tmp->buff != NULL)
			free(tmp->buff);
		i = 0;
		if (tmp->id_strings != NULL)
		{
			while (tmp->id_strings[i] != NULL)
			{
				free(tmp->id_strings[i]);
				i++;
			}
			free(tmp->id_strings);
		}
		free(tmp);
	}
	ft_dlist_clear(&prm->dlist);
	return ((err_code >= 0) ? 0 : ft_error(err_code));
}
