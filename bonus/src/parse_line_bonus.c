/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 14:37:08 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/16 16:05:00 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d_bonus.h"
#include "cub_macro_bonus.h"
#include "ft_utils_bonus.h"

static int	clear_buffer(char **tmp, int ret)
{
	int		i;

	i = 0;
	while (tmp[i] != NULL)
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	tmp = NULL;
	return (ret);
}

static int	check_identifier(char *str, char **id_strings)
{
	int	i;

	i = 0;
	while (id_strings[i] != NULL)
	{
		if (ft_strcmp(str, id_strings[i]))
			return (i);
		i++;
	}
	return (-1);
}

int			parse_line(t_param *prm)
{
	t_parse		*ptr;
	char		**tmp;
	int			id;

	ptr = ((t_parse*)(prm->ptr));
	tmp = ft_split(ptr->buff, WHITESPACES);
	if (prm->booleans & MAP_SET)
		return (clear_buffer(tmp, CONF_AFTER_MAP));
	if ((id = check_identifier(tmp[0], ptr->id_strings)) < 0)
		return (clear_buffer(tmp, WRONG_ID_STR));
	if (id == ID_RES)
		return (clear_buffer(tmp, id_res_filler(prm, tmp)));
	else if (id >= ID_TX_NO && id <= ID_TX_CM)
		return (clear_buffer(tmp, id_path_filler(prm, tmp, id)));
	return (clear_buffer(tmp, 0));
}
