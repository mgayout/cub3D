/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:39:01 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/22 11:39:25 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D_bonus.h"

void	draw_minimap_block(t_data *data, t_map *tmp, int i)
{
	int	color;

	if (i == 40)
	{
		color = create_rgb(255, 0, 0);
		data->draw.buff_mini[90][90] = color;
		data->draw.buff_mini[90][91] = color;
		data->draw.buff_mini[91][90] = color;
		data->draw.buff_mini[91][91] = color;
	}
	else if (tmp->content == 'D' && data->key.door)
		draw_minimap_buffer(data, create_rgb(0, 0, 255), i);
	else if (tmp->content == '1')
		draw_minimap_buffer(data, create_rgb(255, 255, 255), i);
}

void	draw_minimap_buffer(t_data *data, int color, int i)
{
	int	x;
	int	y;
	int	xmax;
	int	ymax;

	y = (i / 9) * 20;
	ymax = y + 20;
	while (y < ymax)
	{
		x = (i % 9) * 20;
		xmax = x + 20;
		while (x < xmax)
		{
			if ((y >= ymax - 19 && y <= ymax - 1)
				&& (x >= xmax - 19 && x <= xmax - 1))
				data->draw.buff_mini[y][x] = color;
			x++;
		}
		y++;
	}
}
