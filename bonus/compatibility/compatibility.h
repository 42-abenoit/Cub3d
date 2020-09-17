/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compatibility.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 17:09:13 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/17 17:27:47 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPATIBILITY_H
# define COMPATIBILITY_H
# ifdef Darwin
#  include <CoreGraphics/CoreGraphics.h>
# endif
# ifdef Linux

int				CGMainDisplayID(void);
int				CGDisplayPixelsWide(int display_id);
int				CGDisplayPixelsHigh(int display_id);
# endif
#endif
