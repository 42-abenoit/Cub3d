/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_trigger.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 20:43:25 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/16 15:57:52 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "cub3d.h"
#include "cub_macro.h"
#include "ft_utils.h"

static int	open_path(t_parse *tmp)
{
	if (!(tmp->id_strings = ft_split(ID_STRINGS, "/")))
		return (ID_SPLIT_ERR);
	tmp->fd = open(tmp->buff, O_RDONLY);
	free(tmp->buff);
	tmp->buff = 0;
	if (read(tmp->fd, &tmp->buff, 0) < 0)
		return (WRONG_FILE_PATH);
	return (1);
}

static int	verify_conf(t_param *prm)
{
	int			ret;

	if ((prm->booleans & CONF_SET) != CONF_SET)
		return (ft_exit(MISS_CONF_INFO, prm));
	if (!(prm->booleans & MAP_SET))
		return (ft_exit(NO_MAP_FOUND, prm));
	if ((ret = player_init(prm)) < 0)
		return (ft_exit(ret, prm));
	clean_parse(prm);
	return (game_struct_init(prm));
}

int			parse_trigger(t_param *prm)
{
	t_parse		*tmp;
	int			ret;

	tmp = ((t_parse*)(prm->ptr));
	if ((ret = open_path(tmp)) < 0)
		return (ft_exit(ret, prm));
	while (rec_gnl(tmp->fd, &tmp->buff) >= 1)
	{
		if (ft_isset(tmp->buff[0], IS_ID))
		{
			if ((ret = parse_line(prm)) < 0)
				return (ft_exit(ret, prm));
		}
		else if (ft_isset(tmp->buff[0], MAP_VALID_CHAR)
					|| ft_isset(tmp->buff[0], WHITESPACES))
		{
			if ((ret = parse_map(prm)) < 0)
				return (ft_exit(ret, prm));
		}
		else if (ft_strlen(tmp->buff) > 0)
			return (ft_exit(NOT_ID_CHAR, prm));
		free(tmp->buff);
		tmp->buff = NULL;
	}
	return (verify_conf(prm));
}
