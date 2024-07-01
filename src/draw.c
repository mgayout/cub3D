/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:41:19 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/01 12:47:18 by mgayout          ###   ########.fr       */
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
			mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.voidd, (tmp->x - 1) * data->pixel, (tmp->y - 1) * data->pixel);
		printf("x = %d | y = %d\n", tmp->x, tmp->y);
		//else if (tmp->content == 'P')
			//mlx_put_image_to_window(data->mlx, data->mlx_win, img, tmp->x, tmp->y);
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
