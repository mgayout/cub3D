/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:08:16 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/11 11:13:00 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	init_size(t_data *data)
{
	data->size.screen_width = 1500;
	data->size.screen_height = 1000;
	xy_max(data);
	block_size(data);
	data->size.moovex = 0;
	data->size.moovey = 0;
}

void	xy_max(t_data *data)
{
	t_map	*tmp;
	int		x;
	int		y;

	tmp = data->parse.map;
	x = 0;
	y = 0;
	while (tmp)
	{
		if (tmp->x > x && tmp->content == '1')
			x = tmp->x;
		if (tmp->y > y && tmp->content == '1')
			y = tmp->y;
		tmp = tmp->next;
	}
	data->size.xmax = x + 1;
	data->size.ymax = y + 1;
}

void	block_size(t_data *data)
{
	data->size.block = 50;
	data->size.wall = data->size.block - 1;
	data->size.player= 10;
}
