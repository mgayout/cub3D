/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:02:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/02 08:36:54 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	init_img(t_data *data)
{
	data->img.wall.mlx_img = mlx_new_image(data->mlx, data->pos.width, data->pos.height);
	data->img.wall.addr = mlx_get_data_addr(data->img.wall.mlx_img, &data->img.wall.bpp, &data->img.wall.line_len, &data->img.wall.endian);
	render_background(data, &data->img.wall, 0xFFFFFF);
	data->img.player.mlx_img = mlx_new_image(data->mlx, data->pos.width, data->pos.height);
	data->img.player.addr = mlx_get_data_addr(data->img.player.mlx_img, &data->img.player.bpp, &data->img.player.line_len, &data->img.player.endian);
	render_background(data, &data->img.player, 0xFF0000);
	data->img.air.mlx_img = mlx_new_image(data->mlx, data->pos.width, data->pos.height);
	data->img.air.addr = mlx_get_data_addr(data->img.air.mlx_img, &data->img.air.bpp, &data->img.air.line_len, &data->img.air.endian);
	render_background(data, &data->img.air, 0);
}

void	render_background(t_data *data, t_texture *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->pos.height)
	{
		j = 0;
		while (j < data->pos.width)
		{
			img_pix_put(img, j++, i, color);
		}
		++i;
	}
}

void	img_pix_put(t_texture *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}