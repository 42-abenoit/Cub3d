/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 14:37:08 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/20 18:21:26 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"
#include "cub_macro.h"
#include "ft_utils.h"

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
	if ((id = check_identifier(tmp[0], ptr->id_strings)) < 0)
		return (clear_buffer(tmp, WRONG_ID_STR));
	if (id == ID_RES)
		return (clear_buffer(tmp, id_res_filler(prm, tmp)));
	else if (id >= ID_TX_NO && id <= ID_TX_S)
		return (clear_buffer(tmp, id_fd_filler(prm, tmp, id)));
	else if (id >= ID_HCC_F && id <= ID_HCC_C)
		return (clear_buffer(tmp, id_hcc_filler(prm, tmp, id)));
	return (clear_buffer(tmp, 0));
}
