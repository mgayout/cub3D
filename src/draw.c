/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:41:19 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/01 15:49:16 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	draw(t_data *data)
{
	t_map	*tmp;

	tmp = data->map;
	while (tmp)
	{
		if (tmp->content == '1')
			mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.wall.mlx_img, (tmp->x - 1) * data->width, (tmp->y - 1) * data->height);
		else if (tmp->content == 'P')
			mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.player.mlx_img, (((tmp->x - 1) * data->width)) + data->x, (((tmp->y - 1) * data->height)) + data->y);
		tmp = tmp->next;
	}
	return (0);
}

void	print_square(t_data *data, int x, int y, int color)
{
	int	xmin;
	int	ymin;

	ymin = y * 50;
	while (ymin <= ((y + 1) * 50))
	{
		xmin = x * 50;
		while (xmin <= ((x + 1) * 50))
		{
			mlx_pixel_put(data->mlx, data->mlx_win, xmin, ymin, color);
			xmin++;
		}
		ymin++;
	}
}
