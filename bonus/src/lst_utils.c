/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 12:27:46 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/26 17:59:28 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"
#include "cub_macro.h"
#include "ft_utils.h"

t_list		*get_lst_elem(t_list *alst, int type)
{
	t_list *ptr;

	if (alst == NULL)
		return (NULL);
	ptr = alst;
	while (ptr != NULL)
	{
		if (ptr->type == type)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

t_list		*ft_lstnew(int type, void *content)
{
	t_list *new;

	if (!(new = malloc(sizeof(t_list))))
		return (NULL);
	new->type = type;
	new->content = content;
	new->next = NULL;
	return (new);
}

void		ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *first;

	if (new == NULL || alst == NULL)
		return ;
	if (*alst == NULL)
		*alst = new;
	else
	{
		first = *alst;
		while (first->next != NULL)
			first = first->next;
		first->next = new;
		new->next = NULL;
	}
}
