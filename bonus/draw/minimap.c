/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:24:00 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/17 18:23:47 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D_bonus.h"

void	draw_minimap(t_data *data)
{
	t_map	*tmp;
	int		x;
	int		y;

	y = -1;
	while (++y != 240)
	{
		x = -1;
		while (++x != 240)
		{
			if ((x >= 20 && x <= 220) && (y >= 20 && y <= 220))
			{
				tmp = find_minimap_pos(data, x, y);
				if (tmp && tmp->content == '1')
					x = draw_minimap_wall(data, x, y);
				else if (tmp && (tmp->content == 'D' && data->key.minimap))
					x = draw_minimap_door(data, x, y);
				else if (tmp && (tmp->content == 'N' || tmp->content == 'E'
					|| tmp->content == 'S' || tmp->content == 'W'))
					x = draw_minimap_player(data, x, y);
				else
					data->draw.buffer[y][x] = 0;
			}
			else
				data->draw.buffer[y][x] = 0;
		}
	}
}

t_map	*find_minimap_pos(t_data *data, int x, int y)
{
	t_map	*tmp;

	if ((y / 20) < 5 || ((y / 20) == 5 && (x / 20) < 5))
		tmp = find_prev_pos(data, x, y);
	else if ((y / 20) > 5 || ((y / 20) == 5 && (x / 20) > 5))
		tmp = find_next_pos(data, x, y);
	else
		tmp = find_player(data);
	return (tmp);
}

t_map	*find_prev_pos(t_data *data, int x, int y)
{
	t_map	*tmp;
	int		i;
	
	i = 0;
	while (tmp && i != (y / 20))
	{
		tmp = find_block(data->parse.map, tmp->x, tmp->y - 1);
		i++;
	}
	i = 0;
	while (tmp && (i != (x / 20)))
	{
		tmp = tmp->prev;
		i++;
	}
	return (tmp);
}

t_map	*find_next_pos(t_data *data, int x, int y)
{
	t_map	*tmp;
	int		i;
	
	i = 0;
	while (tmp && i != (y / 20))
	{
		tmp = find_block(data->parse.map, tmp->x, tmp->y + 1);
		i++;
	}
	i = 0;
	while (tmp && (i != (x / 20)))
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}

int	draw_minimap_wall(t_data *data, int x, int y)
{
	int	newx;
	
	newx = x;
	while (newx != (x + 20))
	{
		if (newx == x || newx == (x + 19))
			data->draw.buffer[y][x] = 0;
		else
			data->draw.buffer[y][x] = 0xFFFFFF;
		newx++;
	}
	return (newx);
}

int	draw_minimap_door(t_data *data, int x, int y)
{
	int	newx;
	
	newx = x;
	while (newx != (x + 20))
	{
		if (newx == x || newx == (x + 19))
			data->draw.buffer[y][x] = 0;
		else
			data->draw.buffer[y][x] = 0x0000FF;
		newx++;
	}
	return (newx);
}

int	draw_minimap_player(t_data *data, int x, int y)
{
	int	newx;
	
	newx = x;
	while (newx != (x + 20))
	{
		if (newx == 10 || newx == 11)
			data->draw.buffer[y][x] = 0xFF0000;
		else
			data->draw.buffer[y][x] = 0;
		newx++;
	}
	return (newx);
}
