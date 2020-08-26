/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 20:13:48 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/26 18:06:16 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"
#include "cub_macro.h"
#include "ft_utils.h"

int		clean_parse(t_param *prm)
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
		free(prm->ptr);
		prm->ptr = NULL;
	}
	return (0);
}

int		clean_render(t_param *prm)
{
	int			id;
	t_list		*ptr;
	t_render	*render;

	id = ID_TX_NO;
	if (prm->ptr != NULL)
	{
		render = ((t_render*)(prm->ptr));
		while (id <= ID_TX_S)
		{
			ptr = get_lst_elem(prm->dlist, id);
			my_mlx_destroy_tx(render->mlx, ptr);
			id++;
		}
		if (render->mlx != NULL)
			free(render->mlx);
		if (render->win != NULL)
			free(render->win);
		free(render);
	}
	return (0);
}

int		ft_exit(int err_code, t_param *prm)
{
	if ((prm->booleans & PARSE_END) < PARSE_END)
		clean_parse(prm);
	else
		clean_render(prm);
	ft_dlist_clear(&prm->dlist);
	return ((err_code >= 0) ? 0 : ft_error(err_code));
}
