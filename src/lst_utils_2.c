/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 18:27:12 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/26 18:06:53 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"
#include "cub_macro.h"
#include "ft_utils.h"

void		ft_lst_delone(t_list **lst, t_list *one)
{
	t_list *ptr;

	if (lst == NULL || one == NULL)
		return ;
	if (*lst == one)
	{
		*lst = (*lst)->next;
		ft_lstclear_content(one);
		one = NULL;
	}
	else
	{
		ptr = *lst;
		while (ptr->next != NULL)
		{
			if (ptr->next == one)
			{
				ptr->next = one->next;
				ft_lstclear_content(one);
				one = NULL;
			}
			else
				ptr = ptr->next;
		}
	}
}

void		ft_lstclear_content(t_list *lst)
{
	t_map	*ptr;
	int		i;

	if (lst->type == ID_MAP)
	{
		ptr = (t_map*)(lst->content);
		i = 0;
		while (ptr->grid[i])
		{
			free(ptr->grid[i]);
			ptr->grid[i] = NULL;
			i++;
		}
		free(ptr->grid);
		ptr->grid = NULL;
	}
	free(lst->content);
	free(lst);
	lst = NULL;
}

void		ft_dlist_clear(t_list **lst)
{
	t_list *ptr;

	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		ptr = (*lst)->next;
		ft_lstclear_content(*lst);
		*lst = ptr;
	}
	*lst = NULL;
}
