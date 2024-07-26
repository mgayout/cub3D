/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 08:59:10 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/26 08:59:10 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D_bonus.h"

void	draw(t_data *data)
{
	data->draw.img.mlx_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->draw.img.addr = mlx_get_data_addr(data->draw.img.mlx_img,
			&data->draw.img.bpp, &data->draw.img.line_len,
			&data->draw.img.endian);
	init_buffer(data);
	draw_cf(data);
	draw_wall(data);
	init_img(data);
	if (data->key.minimap)
		init_minimap(data);
}

void	init_buffer(t_data *data)
{
	int	i;

	i = -1;
	data->draw.buffer = malloc(sizeof(int *) * HEIGHT);
	while (++i < HEIGHT)
		data->draw.buffer[i] = malloc(sizeof(int) * WIDTH);
}

void	draw_cf(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < (HEIGHT / 2))
	{
		x = -1;
		while (++x < WIDTH)
			data->draw.buffer[y][x] = data->texture.c_wall;
	}
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			data->draw.buffer[y][x] = data->texture.f_wall;
	}
}

void	draw_wall(t_data *data)
{
	int	i;

	i = -1;
	while (++i < WIDTH)
	{
		init_ray(&data->ray);
		data->ray.camera = 2 * i / (double)WIDTH - 1;
		data->ray.ray_dirx = data->player.dirx + data->player.planex
			* data->ray.camera;
		data->ray.ray_diry = data->player.diry + data->player.planey
			* data->ray.camera;
		data->ray.mapx = (int)data->player.posx;
		data->ray.mapy = (int)data->player.posy;
		calculate_delta(data);
		calculate_side_dist(data);
		if (exec_dda(data)->content == 'D')
			data->ray.door = 1;
		calc_perp_wall_dist(data);
		calc_height_wall(data);
		init_tex_dir(data);
		calc_wall_x(data);
		calc_x_coord_tex(data);
		color_x_stripe(data, i);
	}
}

void	init_img(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			my_mlx_pixel_put(&data->draw.img, x, y, data->draw.buffer[y][x]);
	}
	free_buffer(data->draw.buffer, 0);
	mlx_put_image_to_window(data->mlx, data->mlx_win,
		data->draw.img.mlx_img, 0, 0);
	mlx_destroy_image(data->mlx, data->draw.img.mlx_img);
}
