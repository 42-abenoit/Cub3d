/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 15:06:16 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/20 16:25:41 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include "cub_struct.h"

/*
**	str_utils.c
*/
void			ft_putchar(char c);
void			ft_putstr(char *str);
int				ft_strlen(char *str);
int				ft_isset(char c, const char *set);
int				ft_strcmp(char *s1, char *s2);

/*
**	str_utils_2.c
*/
char			*ft_strdup(const char *s1);
int				ft_atoi_base(char *str, char *set);

/*
**	lst_utils.c
*/
t_list			*get_lst_elem(t_list *alst, int type);
t_list			*ft_lstnew(int type, void *content);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_dlist_clear(t_list **lst);

/*
**	lst_utils_2.c
*/
void			ft_clear_content_data(t_data *content);

/*
**	ft_split.c
*/
char			**ft_split(char const *s, char *set);

/*
**	ft_strtrim.c
*/
char			*ft_strtrim(char const *s1, char const *set);

/*
**	rec_gnl.c
*/
int				rec_gnl(int fd, char **line);

#endif
