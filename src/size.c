/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:08:16 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/08 17:19:25 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

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
	data->size.block_width = 50;
	data->size.block_height = 50;
	data->size.wall_width = data->size.block_width - 1;
	data->size.wall_height = data->size.block_height - 1;
	data->size.player_width = 10;
	data->size.player_height = 10;
}

