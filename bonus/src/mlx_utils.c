/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 17:24:29 by abenoit           #+#    #+#             */
/*   Updated: 2020/09/10 17:34:31 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub_struct.h"
#include "cub_macro.h"
#include "mlx.h"

int		get_pixel_color(int x, int y, t_data *img)
{
	int		color;
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color = *(unsigned int*)dst;
	return (color);
}

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_data	my_mlx_new_image(void *mlx, int width, int height)
{
	t_data	img;

	img.img = mlx_new_image(mlx, width, height);
	img.addr = mlx_get_data_addr(img.img,
						&(img.bits_per_pixel), &(img.line_length),
						&(img.endian));
	return (img);
}

int		my_mlx_destroy_tx(void *mlx, t_list *elem)
{
	t_tx	*tx;

	if (elem->content == NULL)
		return (0);
	tx = (t_tx*)elem->content;
	mlx_destroy_image(mlx, tx->data.img);
	free(elem->content);
	elem->content = NULL;
	return (0);
}

int		my_mlx_tx_from_path(void *mlx, t_list *elem)
{
	t_tx	*tx;

	if (!(tx = malloc(sizeof(t_tx))))
		return (TX_IMPORT_FAIL);
	tx->data.img = mlx_xpm_file_to_image(mlx, (char*)elem->content,
					&tx->height, &tx->width);
	tx->data.addr = mlx_get_data_addr(tx->data.img,
			&(tx->data.bits_per_pixel), &(tx->data.line_length),
			&(tx->data.endian));
	free(elem->content);
	elem->content = tx;
	return (0);
}
