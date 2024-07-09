/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:49:12 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/09 13:49:14 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D_bonus.h"

void	xy_max(t_data *data)
{
	t_map	*tmp;
	int		x;
	int		y;

	tmp = data->map;
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

void	mini_size(t_data *data)
{
	data->size.minimap.mini_width = 275;
	data->size.minimap.mini_height = 275;
	data->size.minimap.block = (data->size.block / 2);
	data->size.minimap.wall = data->size.minimap.block - 1;
	data->size.minimap.player = data->size.player / 2;
}
