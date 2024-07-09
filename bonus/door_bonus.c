/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:46:39 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/09 13:46:45 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D_bonus.h"

int	init_door(t_data *data)
{
	t_map	*tmp;
	int		posx;
	int		posy;

	tmp = data->map;
	if (data->door == false)
	{
		while (tmp)
		{
			posx = (tmp->x * data->size.block) + ((data->size.block - data->size.wall) / 2);
			posy = (tmp->y * data->size.block) + ((data->size.block - data->size.wall) / 2);
			if (tmp->content == 'D')
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.air.mlx_img, posx, posy);
			tmp = tmp->next;
		}
		data->door = true;
	}
	else if (data->door == true && player_on_wall(data))
	{
		while (tmp)
		{
			posx = (tmp->x * data->size.block) + ((data->size.block - data->size.wall) / 2);
			posy = (tmp->y * data->size.block) + ((data->size.block - data->size.wall) / 2);
			if (tmp->content == 'D')
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.door.mlx_img, posx, posy);
			tmp = tmp->next;
		}
		data->door = false;
	}
	return (1);
}

int	next_to_door(t_data *data, int x, int y)
{
	t_map	*tmp;
	int		up;
	int		right;
	int		down;
	int		left;

	tmp = data->map;
	while (tmp->content != 'N' && tmp->content != 'E' && tmp->content != 'S' && tmp->content != 'W')
		tmp = tmp->next;
	up = (tmp->y * data->size.block) + ((data->size.block - data->size.player) / 2) + (data->size.moovey + y);
	right = ((tmp->x + 1) * data->size.block) - ((data->size.block - data->size.player) / 2) + (data->size.moovex + x);
	down = ((tmp->y + 1) * data->size.block) - ((data->size.block - data->size.player) / 2) + (data->size.moovey + y);
	left = (tmp->x * data->size.block) + ((data->size.block - data->size.player) / 2) + (data->size.moovex + x);
	if (find_block_pixel(data, left, up)->content == 'D')
		return (1);
	else if (find_block_pixel(data, right, up)->content == 'D')
		return (1);
	else if (find_block_pixel(data, right, down)->content == 'D')
		return (1);
	else if (find_block_pixel(data, left, down)->content == 'D')
		return (1);
	return (0);
}

int	player_on_wall(t_data *data)
{
	t_map	*player;
	int		posx;
	int		posy;

	player = find_player(data);
	posx = (player->x * data->size.block) + ((data->size.block - data->size.player) / 2) + data->size.moovex;
	posy = (player->y * data->size.block) + ((data->size.block - data->size.player) / 2) + data->size.moovey;
	if (find_block_pixel(data, posx, posy)->content == 'D')
		return (0);
	return (1);
}
