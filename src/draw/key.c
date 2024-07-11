/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:38:48 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/11 15:41:27 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

int	press_key(int key, t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (key == XK_Escape)
		free_all(data);
	else if (key == XK_w || key == XK_Up)
		y -= 5;
	else if (key == XK_a || key == XK_Left)
		x -= 5;
	else if (key == XK_d || key == XK_Right)
		x += 5;
	else if (key == XK_s || key == XK_Down)
		y += 5;
	else
		return (1);
	if (walled(data, x, y))
		return (1);
	update_player(data, x, y);
	return (1);
}

int	walled(t_data *data, int x, int y)
{
	t_map	*tmp;
	int		up;
	int		right;
	int		down;
	int		left;

	tmp = data->parse.map;
	while (tmp->content != 'N' && tmp->content != 'E' && tmp->content != 'S' && tmp->content != 'W')
		tmp = tmp->next;
	up = (tmp->y * data->size.block) + ((data->size.block - data->size.player) / 2) + (data->size.moovey + y);
	right = ((tmp->x + 1) * data->size.block) - ((data->size.block - data->size.player) / 2) + (data->size.moovex + x);
	down = ((tmp->y + 1) * data->size.block) - ((data->size.block - data->size.player) / 2) + (data->size.moovey + y);
	left = (tmp->x * data->size.block) + ((data->size.block - data->size.player) / 2) + (data->size.moovex + x);
	if (find_block_pixel(data, left, up)->content == '1')
		return (1);
	else if (find_block_pixel(data, right, up)->content == '1')
		return (1);
	else if (find_block_pixel(data, right, down)->content == '1')
		return (1);
	else if (find_block_pixel(data, left, down)->content == '1')
		return (1);
	return (0);
}
