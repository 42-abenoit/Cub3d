/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_filler_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 14:51:05 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/25 17:58:52 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"
#include "cub_macro.h"
#include "ft_utils.h"

static int	hcc_clean_exit(int ret, void *elem)
{
	free(elem);
	return (ret);
}

static int	hcc_extract(unsigned int *hcc, int *j, char **buff)
{
	int		i;
	int		tmp;

	i = 0;
	while (buff[i] != NULL)
	{
		if (ft_strlen(buff[i]) != 0)
		{
			if (ft_contains_notset(buff[i], BASE_10))
				return (WRONG_HCC_CHAR);
			if ((tmp = ft_atoi_base(buff[i], BASE_10)) < 256 && tmp >= 0)
				*hcc += tmp << ((*j * 8) - 8);
			else
				return (WRONG_HCC_VAL);
			*j -= 1;
		}
		free(buff[i]);
		i++;
	}
	free(buff);
	if (*j < 0)
		return (WRONG_HCC_ELEM);
	else
		return (*j);
}

static int	create_hcc_list(t_param *prm, int id,
			t_hcc *hcc, const int *bitmask)
{
	ft_lstadd_back(&(prm->dlist), ft_lstnew(id, hcc));
	if (get_lst_elem(prm->dlist, id) == NULL)
		return (hcc_clean_exit(MAL_ERR_LIST, hcc));
	prm->booleans += bitmask[id - 6];
	return (0);
}

int			id_hcc_filler(t_param *prm, char **elem, int id)
{
	int			i;
	int			j;
	t_hcc		*hcc;
	char		**buff;
	const int	bitmask[] = {HCC_F_SET, HCC_C_SET};

	if (prm->booleans & bitmask[id - 6])
		return (HCC_ALRD_SET);
	if (!(hcc = malloc(sizeof(t_hcc))))
		return (MAL_ERR_HCC);
	i = 1;
	j = 3;
	hcc->hcc = 0;
	while (elem[i] != NULL)
	{
		buff = ft_split(elem[i], ",");
		if ((j = hcc_extract(&(hcc->hcc), &j, buff)) < 0)
			return (hcc_clean_exit(j, hcc));
		i++;
	}
	if (j > 0)
		return (hcc_clean_exit(WRONG_HCC_ELEM, hcc));
	return (create_hcc_list(prm, id, hcc, bitmask));
}
