/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:02:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/17 16:23:46 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D_bonus.h"

void	init_texture(t_data *data)
{
	char	**arg;

	arg = ft_split(data->parse.texture_path[5], ',');
	if (arg)
	{
		data->texture.c_wall = create_rgb(ft_atoi(arg[0]),
				ft_atoi(arg[1]), ft_atoi(arg[2]));
		free_tab(arg);
	}
	arg = ft_split(data->parse.texture_path[6], ',');
	if (arg)
	{
		data->texture.f_wall = create_rgb(ft_atoi(arg[0]),
				ft_atoi(arg[1]), ft_atoi(arg[2]));
		free_tab(arg);
	}
	wall_texture(data);
	data->texture.door.mlx_img = mlx_xpm_file_to_image(data->mlx,
			data->parse.texture_path[4], &data->texture.door.tex_width,
			&data->texture.door.tex_height);
	data->texture.door.addr = mlx_get_data_addr(data->texture.door.mlx_img,
			&data->texture.door.bpp, &data->texture.door.line_len,
			&data->texture.door.endian);
}

void	wall_texture(t_data *data)
{
	data->texture.nwall.mlx_img = mlx_xpm_file_to_image(data->mlx,
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
			&data->texture.wwall.endian);
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
