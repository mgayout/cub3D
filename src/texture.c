/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:02:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/09 16:44:09 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	create_texture(t_data *data)
{
	data->texture.nwall = mlx_xpm_file_to_image(data->mlx, data->texture.nwall_path, 0, 0);
	data->texture.ewall = mlx_xpm_file_to_image(data->mlx, data->texture.ewall_path, 0, 0);
	data->texture.swall = mlx_xpm_file_to_image(data->mlx, data->texture.swall_path, 0, 0);
	data->texture.wwall = mlx_xpm_file_to_image(data->mlx, data->texture.wwall_path, 0, 0);
	
	data->texture.wall.mlx_img = mlx_new_image(data->mlx, data->size.wall, data->size.wall);
	data->texture.wall.addr = mlx_get_data_addr(data->texture.wall.mlx_img, &data->texture.wall.bpp,
								&data->texture.wall.line_len, &data->texture.wall.endian);
	render_background(data, &data->texture.wall, 0xFFFFFF);

	data->texture.player.mlx_img = mlx_new_image(data->mlx, data->size.player, data->size.player);
	data->texture.player.addr = mlx_get_data_addr(data->texture.player.mlx_img, &data->texture.player.bpp,
								&data->texture.player.line_len, &data->texture.player.endian);
	render_background(data, &data->texture.player, 0xFF0000);
	
	data->texture.air_player.mlx_img = mlx_new_image(data->mlx, data->size.player, data->size.player);
	data->texture.air_player.addr = mlx_get_data_addr(data->texture.air_player.mlx_img, &data->texture.air_player.bpp,
								&data->texture.air_player.line_len, &data->texture.air_player.endian);
	render_background(data, &data->texture.air_player, 0);
}

void	render_background(t_data *data, t_tmp *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->size.block)
	{
		j = 0;
		while (j < data->size.block)
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
