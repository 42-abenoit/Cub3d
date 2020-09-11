/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 13:09:48 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/11 17:02:55 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include "ft_utils.h"
#include "cub_macro.h"
#include "cub_struct.h"

static int	apply_ratio_to_channel(int color_input, int ratio,
									int color_mod, int channel)
{
	int			color;

	color = ((int)(((1.0 - ratio)
						* (double)(color_input & channel))
						+ (ratio
						* (double)(color_mod & channel)))
						& channel);
	return (color);
}

int			apply_fog(double dist, int color_input, t_param *prm)
{
	double		fog_percent;
	int			color;
	t_conf		*conf;

	conf = get_lst_elem(prm->dlist, ID_CONF)->content;
	color = 0;
	if ((color_input & 0x00FFFFFF) != 0)
	{
		fog_percent = fabs(dist) / conf->view_depth;
		if (fog_percent > 1.0)
			fog_percent = 1.0;
		color = 0;
		color += apply_ratio_to_channel(color_input, fog_percent, conf->fog_color, 0x000000FF);
		color += apply_ratio_to_channel(color_input, fog_percent, conf->fog_color, 0x0000FF00);
		color += apply_ratio_to_channel(color_input, fog_percent, conf->fog_color, 0x00FF0000);
	}
	return (color);
}

int			apply_hit_effect(int color_input)
{
	int			color;

	color = 0;
	if ((color_input & 0x00FFFFFF) != 0)
	{
		color = 0;
		color += ((int)((0.5  * (double)(color_input & 0x000000FF)) + (0.5 * (double)(0x00FFFF00 & 0x000000FF))) & 0x000000FF);
		color += ((int)((0.5 * (double)(color_input & 0x0000FF00)) + (0.5 * (double)(0x00FFFF00 & 0x0000FF00))) & 0x0000FF00);
		color += ((int)((0.5 * (double)(color_input & 0x00FF0000)) + (0.5 * (double)(0x00FFFF00 & 0x00FF0000))) & 0x00FF0000);
	}
	return (color);
}