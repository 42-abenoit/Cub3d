/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 20:13:48 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/19 14:53:08 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"

int		ft_exit(int err_code, t_param *prm)
{
	t_parse		*tmp;
	int			i;

	tmp = ((t_parse*)(prm->ptr));
	free(tmp->buff);
	i = 0;
	while (tmp->id_strings[i] != NULL)
	{
		free(tmp->id_strings[i]);
		(tmp->id_strings[i]) = NULL;
		i++;
	}
	free(tmp->id_strings);
	free(prm->ptr);
	if (err_code == 0)
		return (0);
	else
		return (ft_error(err_code));
}
