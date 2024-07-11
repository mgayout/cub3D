/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:02:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/11 14:54:06 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	create_texture(t_data *data)
{
	char	**arg;

	arg = ft_split(data->parse.texture_path[4], ',');
	if (arg)
	{
		data->texture.c_wall = create_rgb(ft_atoi(arg[0]), ft_atoi(arg[1]), ft_atoi(arg[2]));
		free_tab(arg);
	}
	arg = ft_split(data->parse.texture_path[5], ',');
	if (arg)
	{
		data->texture.f_wall = create_rgb(ft_atoi(arg[0]), ft_atoi(arg[1]), ft_atoi(arg[2]));
		free_tab(arg);
	}
	/*data->texture.nwall.mlx_img = mlx_xpm_file_to_image(data->mlx,
			data->parse.texture_path[0], &data->texture.nwall.tex_width,
			&data->texture.nwall.tex_height);
	data->texture.nwall.addr = mlx_get_data_addr(data->texture.nwall.mlx_img,
			&data->texture.nwall.bpp, &data->texture.nwall.line_len,
			&data->texture.nwall.endian);
	data->texture.ewall.mlx_img = mlx_xpm_file_to_image(data->mlx,
			data->parse.texture_path[1], &data->texture.ewall.tex_width,
			&data->texture.ewall.tex_height);
	data->texture.ewall.addr = mlx_get_data_addr(data->texture.ewall.mlx_img,
			&data->texture.ewall.bpp, &data->texture.ewall.line_len,
			&data->texture.ewall.endian);
	data->texture.swall.mlx_img = mlx_xpm_file_to_image(data->mlx,
			data->parse.texture_path[2], &data->texture.swall.tex_width,
			&data->texture.swall.tex_height);
	data->texture.swall.addr = mlx_get_data_addr(data->texture.swall.mlx_img,
			&data->texture.swall.bpp, &data->texture.swall.line_len,
			&data->texture.swall.endian);
	data->texture.wwall.mlx_img = mlx_xpm_file_to_image(data->mlx,
			data->parse.texture_path[3], &data->texture.wwall.tex_width,
			&data->texture.wwall.tex_height);
	data->texture.wwall.addr = mlx_get_data_addr(data->texture.wwall.mlx_img,
			&data->texture.wwall.bpp, &data->texture.wwall.line_len,
			&data->texture.wwall.endian);*/
	
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

void	render_background(t_data *data, t_tex *img, int color)
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

void	img_pix_put(t_tex *img, int x, int y, int color)
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

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}