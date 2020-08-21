/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_filler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 17:48:41 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/21 14:54:24 by abenoit          ###   ########.fr       */
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
	int		tmp;
	t_data	*data;

	if (prm->booleans & RES_SET)
		return (RES_ALRD_SET);
	if (elem_count(elem) != 3)
		return (WRONG_RES_ELEM);
	if (!(data = malloc(sizeof(t_data))))
		return (MAL_ERR_DATA);
	tmp = ft_atoi_base(elem[1], BASE_10);
	data->img_width = tmp;
	tmp = ft_atoi_base(elem[2], BASE_10);
	data->img_height = tmp;
	ft_lstadd_back(&(prm->dlist), ft_lstnew(ID_RES, data));
	if (get_lst_elem(prm->dlist, ID_RES) == NULL)
		return (id_clean_exit(MAL_ERR_LIST, data));
	prm->booleans += RES_SET;
	return (0);
}

int			id_fd_filler(t_param *prm, char **elem, int id)
{
	t_fd		*fd;
	char		tmp;
	const int	bitmask[] = {0, TX_NO_SET, TX_SO_SET, TX_WE_SET,
		TX_EA_SET, TX_S_SET};

	if (prm->booleans & bitmask[id])
		return (TX_ALRD_SET);
	if (elem_count(elem) != 2)
		return (WRONG_TX_ELEM);
	if (!(fd = malloc(sizeof(t_fd))))
		return (MAL_ERR_TX_FD);
	fd->fd = open(elem[1], O_RDONLY);
	if (read(fd->fd, &tmp, 0) < 0)
		return (WRONG_TX_PATH);
	ft_lstadd_back(&(prm->dlist), ft_lstnew(id, fd));
	if (get_lst_elem(prm->dlist, id) == NULL)
		return (id_clean_exit(MAL_ERR_LIST, fd));
	prm->booleans += bitmask[id];
	return (0);
}
