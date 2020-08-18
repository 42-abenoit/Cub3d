/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 15:06:16 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/18 20:47:53 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

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

/*
**	ft_split.c
*/
char			**ft_split(char const *s, char c);

/*
**	ft_strtrim.c
*/
char			*ft_strtrim(char const *s1, char const *set);

/*
**	rec_gnl.c
*/
int				rec_gnl(int fd, char **line);

#endif
