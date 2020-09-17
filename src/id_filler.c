/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_filler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 17:48:41 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/17 13:52:53 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "cub3d.h"
#include "cub_macro.h"
#include "ft_utils.h"

static int	elem_count(char **elem)
{
	int		i;

	i = 0;
	while (elem[i] != NULL)
		i++;
	return (i);
}

static int	id_clean_exit(int ret, void *elem)
{
	free(elem);
	return (ret);
}

int			id_res_filler(t_param *prm, char **elem)
{
	t_screen	*screen;

	if (prm->booleans & RES_SET)
		return (RES_ALRD_SET);
	if (elem_count(elem) != 3)
		return (WRONG_RES_ELEM);
	if (ft_contains_notset(elem[1], BASE_10)
			|| ft_contains_notset(elem[2], BASE_10))
		return (WRONG_RES_CHAR);
	if (!(screen = malloc(sizeof(t_screen))))
		return (MAL_ERR_SCREEN);
	if ((screen->width = ft_atoi_base(elem[1], BASE_10)) <= 0)
		return (RES_OVERFLOW);
	if ((screen->height = ft_atoi_base(elem[2], BASE_10)) <= 0)
		return (RES_OVERFLOW);
	ft_lstadd_back(&(prm->dlist), ft_lstnew(ID_RES, screen));
	if (get_lst_elem(prm->dlist, ID_RES) == NULL)
		return (id_clean_exit(MAL_ERR_LIST, screen));
	prm->booleans += RES_SET;
	return (0);
}

int			id_path_filler(t_param *prm, char **elem, int id)
{
	int			fd;
	char		*path;
	char		tmp;
	const int	bitmask[] = {0, TX_NO_SET, TX_SO_SET, TX_WE_SET,
		TX_EA_SET, TX_S_SET};

	path = NULL;
	if (prm->booleans & bitmask[id])
		return (TX_ALRD_SET);
	if (elem_count(elem) != 2)
		return (WRONG_TX_ELEM);
	if (!verify_extension(elem[1], XPM_EXT))
		return (WRONG_FILE_EXT);
	fd = open(elem[1], O_RDONLY);
	if (read(fd, &tmp, 0) < 0)
		return (id_clean_exit(WRONG_TX_PATH, path));
	if ((path = ft_strdup(elem[1])) == NULL)
		return (MAL_ERR_TX_PATH);
	ft_lstadd_back(&(prm->dlist), ft_lstnew(id, path));
	if (get_lst_elem(prm->dlist, id) == NULL)
		return (id_clean_exit(MAL_ERR_LIST, path));
	prm->booleans += bitmask[id];
	return (0);
}
