/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:25:01 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/13 13:25:01 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

void	init_buffer(t_data *data)
{
	int	i;
	
	i = -1;
	data->buffer = malloc(sizeof(int *) * HEIGHT);
	while (++i < HEIGHT)
		data->buffer[i] = malloc(sizeof(int) * WIDTH);
}

void	put_cf_in_buffer(t_data *data)
{
	int	x;
	int	y;
	
	y = -1;
	init_buffer(data);
	while (++y < (HEIGHT / 2))
	{
		x = -1;
		while (++x < WIDTH)
			data->buffer[y][x] = data->texture.c_wall;
	}
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			data->buffer[y][x] = data->texture.f_wall;
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
			my_mlx_pixel_put(&data->img, x, y, data->buffer[y][x]);
	}
	free_buffer(data);
}
