/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:38:48 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/18 12:49:11 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D_bonus.h"

void	key_signal(t_data *data)
{
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &press_key, data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, &release_key, data);
	mlx_hook(data->mlx_win, MotionNotify, PointerMotionMask, &mouse, data);
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
	else if (bonus_key(key, data))
		return (1);
	return (1);
}

int	bonus_key(int key, t_data *data)
{
	if (key == XK_m && data->key.minimap)
	{
		data->key.minimap = 0;
		draw(data);
	}
	else if (key == XK_m && !data->key.minimap)
	{
		data->key.minimap = 1;
		draw(data);
	}
	else if (key == XK_o && data->key.door)
	{
		data->key.door = 0;
		draw(data);
	}
	else if (key == XK_o && !data->key.door && find_block(data->parse.map,
			(int)data->player.posx, (int)data->player.posy)->content != 'D')
	{
		data->key.door = 1;
		draw(data);
	}
	else
		return (1);
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
