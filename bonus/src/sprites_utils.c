/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 15:25:44 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/10 16:14:51 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"

t_sprite	*ft_new_sprite(char type, int x, int y)
{
	t_sprite *new;

	if (!(new = malloc(sizeof(t_sprite))))
		return (NULL);
	new->type = type;
	new->hp = rand() % 10 + rand() % 10 + rand() % 10;
	new->pos.x = (double)x + 0.5;
	new->pos.y = (double)y + 0.5;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void		ft_add_sprite_front(t_sprite **alst, t_sprite *new)
{
	if (new == NULL || alst == NULL)
		return ;
	if (*alst == NULL)
		*alst = new;
	else
	{
		new->next = *alst;
		new->prev = NULL;
		(*alst)->prev = new;
		(*alst) = new;
	}
}

void		ft_sprite_switch(t_sprite *ptr)
{
	if (ptr->prev != NULL)
		ptr->prev->next = ptr->next;
	ptr->next->prev = ptr->prev;
	ptr->prev = ptr->next;
	ptr->next = ptr->prev->next;
	ptr->prev->next = ptr;
	if (ptr->next != NULL)
		ptr->next->prev = ptr;
}

void		ft_sprite_sort(t_sprite **lst)
{
	t_sprite	*ptr;

	if (*lst != NULL)
	{
		ptr = (*lst);
		while (ptr->next != NULL)
		{
			if (ptr->next->dist > ptr->dist)
				ft_sprite_switch(ptr);
			if (ptr->next != NULL)
				ptr = ptr->next;
		}
		while (ptr->prev != NULL)
			ptr = ptr->prev;
		(*lst) = ptr;
	}
}

void		ft_clear_list(t_sprite **lst)
{
	t_sprite *ptr;

	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		ptr = (*lst)->next;
		free(*lst);
		*lst = ptr;
	}
	*lst = NULL;
	lst = NULL;
}
