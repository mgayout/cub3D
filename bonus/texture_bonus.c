/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:49:22 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/09 13:49:27 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D_bonus.h"

void	init_texture(t_data *data)
{
	data->texture.nwall_path = NULL;
	data->texture.ewall_path = NULL;
	data->texture.swall_path = NULL;
	data->texture.wwall_path = NULL;
	data->texture.cwall_color = NULL;
	data->texture.fwall_color = NULL;
}

void	create_texture(t_data *data)
{
	data->texture.wall.mlx_img = mlx_new_image(data->mlx, data->size.wall, data->size.wall);
	data->texture.wall.addr = mlx_get_data_addr(data->texture.wall.mlx_img, &data->texture.wall.bpp,
								&data->texture.wall.line_len, &data->texture.wall.endian);
	render_background(data, &data->texture.wall, 0xFFFFFF);
	
	data->texture.air.mlx_img = mlx_new_image(data->mlx, data->size.wall, data->size.wall);
	data->texture.air.addr = mlx_get_data_addr(data->texture.air.mlx_img, &data->texture.air.bpp,
								&data->texture.air.line_len, &data->texture.air.endian);
	render_background(data, &data->texture.air, 0);

	data->texture.player.mlx_img = mlx_new_image(data->mlx, data->size.player, data->size.player);
	data->texture.player.addr = mlx_get_data_addr(data->texture.player.mlx_img, &data->texture.player.bpp,
								&data->texture.player.line_len, &data->texture.player.endian);
	render_background(data, &data->texture.player, 0xFF0000);
	
	data->texture.air_player.mlx_img = mlx_new_image(data->mlx, data->size.player, data->size.player);
	data->texture.air_player.addr = mlx_get_data_addr(data->texture.air_player.mlx_img, &data->texture.air_player.bpp,
								&data->texture.air_player.line_len, &data->texture.air_player.endian);
	render_background(data, &data->texture.air_player, 0);
	
	data->texture.door.mlx_img = mlx_new_image(data->mlx, data->size.wall, data->size.wall);
	data->texture.door.addr = mlx_get_data_addr(data->texture.door.mlx_img, &data->texture.door.bpp,
								&data->texture.door.line_len, &data->texture.door.endian);
	render_background(data, &data->texture.door, 0x0000FF);
	
	data->texture.minimap.background.mlx_img = mlx_new_image(data->mlx, data->size.minimap.mini_width, data->size.minimap.mini_height);
	data->texture.minimap.background.addr = mlx_get_data_addr(data->texture.minimap.background.mlx_img,
								&data->texture.minimap.background.bpp, &data->texture.minimap.background.line_len,
								&data->texture.minimap.background.endian);
	render_background(data, &data->texture.minimap.background, 0);
	data->texture.minimap.wall.mlx_img = mlx_new_image(data->mlx, data->size.minimap.wall, data->size.minimap.wall);
	data->texture.minimap.wall.addr = mlx_get_data_addr(data->texture.minimap.wall.mlx_img,
								&data->texture.minimap.wall.bpp, &data->texture.minimap.wall.line_len,
								&data->texture.minimap.wall.endian);
	render_background(data, &data->texture.minimap.wall, 0xFFFFFF);
	data->texture.minimap.player.mlx_img = mlx_new_image(data->mlx, data->size.minimap.player, data->size.minimap.player);
	data->texture.minimap.player.addr = mlx_get_data_addr(data->texture.minimap.player.mlx_img,
								&data->texture.minimap.player.bpp, &data->texture.minimap.player.line_len,
								&data->texture.minimap.player.endian);
	render_background(data, &data->texture.minimap.player, 0xFF0000);
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