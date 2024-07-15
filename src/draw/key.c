/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:38:48 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/15 14:39:32 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

void	key_signal(t_data *data)
{
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &press_key, data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, &release_key, data);
	mlx_hook(data->mlx_win, 17, 0, &free_all, data);
}

int	press_key(int key, t_data *data)
{
	if (key == XK_Escape)
		free_all(data);
	else if (key == XK_w)
		data->key.up = 1;
	else if (key == XK_a)
		data->key.left = 1;
	else if (key == XK_d)
		data->key.right = 1;
	else if (key == XK_s)
		data->key.down = 1;
	else if (key == XK_Left)
		data->key.cam_left = 1; 
	else if (key == XK_Right)
		data->key.cam_right = 1;
	else
		return (1);
	move(data);
	draw(data);
	return (1);
}

int	release_key(int key, t_data *data)
{
	if (key == XK_w)
		data->key.up = 0;
	else if (key == XK_a)
		data->key.left = 0;
	else if (key == XK_d)
		data->key.right = 0;
	else if (key == XK_s)
		data->key.down = 0;
	else if (key == XK_Left)
		data->key.cam_left = 0; 
	else if (key == XK_Right)
		data->key.cam_right = 0;
	else
		return (1);
	return (1);
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
