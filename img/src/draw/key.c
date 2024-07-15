/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:38:48 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/13 16:29:44 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

int	press_key(int key, t_data *data)
{
	if (key == XK_Escape)
		free_all(data);
	else if (key == XK_w)
		move_w(data);
	else if (key == XK_a)
		move_a(data);
	else if (key == XK_d)
		move_d(data);
	else if (key == XK_s)
		move_s(data);
	else if (key == XK_Left || key == XK_Right)
		modify_rot(data, key);
	else
		return (1);
	update_changes(data);
	/*if (walled(data, x, y))
		return (1);
	update_player(data, x, y);*/
	return (1);
}

void	move_w(t_data *data)
{
	data->ray.x = cos(data->ray.rot) * 5;
	data->ray.y = -sin(data->ray.rot) * 5;
}

void	move_a(t_data *data)
{
	data->ray.x = cos(data->ray.rot + PI / 2) * 5;
	data->ray.y = -sin(data->ray.rot + PI / 2) * 5;
}

void	move_d(t_data *data)
{
	data->ray.x = cos(data->ray.rot - PI / 2) * 5;
	data->ray.y = -sin(data->ray.rot - PI / 2) * 5;
}

void	move_s(t_data *data)
{
	data->ray.x = -cos(data->ray.rot) * 5;
	data->ray.y = sin(data->ray.rot) * 5;
}

void	modify_rot(t_data *data, int key)
{
	if (key == XK_Left)
		data->ray.rot += ROT_SPEED;
	else
		data->ray.rot -= ROT_SPEED;
	data->ray.dirX = cos(data->ray.rot);
	data->ray.dirY = -sin(data->ray.rot);
}

/*int	walled(t_data *data, int x, int y)
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
}*/
