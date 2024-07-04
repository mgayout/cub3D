/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:02:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/04 19:29:24 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	init_texture(t_data *data)
{
	data->texture.wall.mlx_img = mlx_new_image(data->mlx, data->pos.width - 1, data->pos.height - 1);
	data->texture.wall.addr = mlx_get_data_addr(data->texture.wall.mlx_img, &data->texture.wall.bpp, &data->texture.wall.line_len, &data->texture.wall.endian);
	render_background(data, &data->texture.wall, 0xFFFFFF);
	data->texture.player.mlx_img = mlx_new_image(data->mlx, data->pos.width, data->pos.height);
	data->texture.player.addr = mlx_get_data_addr(data->texture.player.mlx_img, &data->texture.player.bpp, &data->texture.player.line_len, &data->texture.player.endian);
	render_background(data, &data->texture.player, 0xFF0000);
	data->texture.air.mlx_img = mlx_new_image(data->mlx, data->pos.width, data->pos.height);
	data->texture.air.addr = mlx_get_data_addr(data->texture.air.mlx_img, &data->texture.air.bpp, &data->texture.air.line_len, &data->texture.air.endian);
	render_background(data, &data->texture.air, 0);
}

void	render_background(t_data *data, t_tmp *img, int color)
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

void	img_pix_put(t_tmp *img, int x, int y, int color)
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