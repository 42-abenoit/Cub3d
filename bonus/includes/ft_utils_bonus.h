/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 15:06:16 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/16 13:38:55 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_BONUS_H
# define FT_UTILS_BONUS_H

# include "cub_struct_bonus.h"

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
int				verify_extension(char *file_name, char *ext);
int				ft_contains_notset(char *str, char *set);

/*
**	lst_utils.c
*/
t_list			*get_lst_elem(t_list *alst, int type);
t_list			*ft_lstnew(int type, void *content);
void			ft_lstadd_back(t_list **alst, t_list *new);

/*
**	lst_utils_2.c
*/
void			ft_lst_delone(t_list **lst, t_list *one);
void			ft_lstclear_content(t_list *lst);
void			ft_dlist_clear(t_list **lst);

/*
**	mlx_utils.c
*/
int				get_pixel_color(int x, int y, t_data *img);
void			my_mlx_pixel_put(t_data *img, int x, int y, int color);
t_data			my_mlx_new_image(void *mlx, int width, int height);
int				my_mlx_destroy_tx(void *mlx, t_list *elem);
int				my_mlx_tx_from_path(void *mlx, t_list *elem);

/*
**	sprite_utils.c
*/
t_sprite		*ft_new_sprite(char type, int x, int y);
void			ft_add_sprite_front(t_sprite **alst, t_sprite *new);
void			ft_sprite_switch(t_sprite *ptr);
void			ft_sprite_sort(t_sprite **lst);
void			ft_clear_list(t_sprite **lst);

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
