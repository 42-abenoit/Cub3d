/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:11:40 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/24 15:47:16 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub_macro.h"
#include "cub3d.h"
#include "ft_utils.h"

static int		prm_init(t_param *prm)
{
	t_parse		*parse_struct;

	prm->booleans = 0;
	if (!(parse_struct = malloc(sizeof(t_parse))))
		return (0);
	prm->ptr = parse_struct;
	prm->dlist = NULL;
	return (1);
}

int				main(int ac, char **av)
{
	t_param	prm;

	if (!(prm_init(&prm)))
		return (ft_exit(MAL_ERR_PARSE_STRUCT, &prm));
	if (ac == 2 || ac == 3)
	{
		if (ac == 3)
		{
			if (!(ft_strcmp(av[2], SAVE_STR)))
				return (ft_exit(WRONG_SAVE_STR, &prm));
			prm.booleans += BMP_SAVE;
		}
		if (verify_extension(av[1], CUB_EXT))
		{
			if (!(((t_parse*)(prm.ptr))->buff = ft_strdup(av[1])))
				return (ft_exit(MAL_ERR_FILENAME, &prm));
			parse_trigger(&prm);
		}
		else
			return (ft_exit(WRONG_FILE_EXT, &prm));
	}
	else
		return (ft_exit(WRONG_ARG_NUM, &prm));
	return (0);
}
