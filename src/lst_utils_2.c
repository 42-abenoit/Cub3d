/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 18:27:12 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/24 18:49:38 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
