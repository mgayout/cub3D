/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:23:06 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/15 14:55:39 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

void	move(t_data *data)
{
	if (data->key.up != 0)
		move_player(data, 0);
	if (data->key.right != 0)
		move_player(data, 1);
	if (data->key.down != 0)
		move_player(data, 2);
	if (data->key.left != 0)
		move_player(data, 3);
	if (data->key.cam_left != 0)
		move_cam(data, -1);
	if (data->key.cam_right != 0)
		move_cam(data, 1);
}

void	move_player(t_data *data, int n)
{
	double	newx;
	double	newy;

	if (n == 0)
	{
		newx = data->player.posx + data->player.dirx * MOVE_SPEED;
		newy = data->player.posy + data->player.diry * MOVE_SPEED;
	}
	else if (n == 1)
	{
		newx = data->player.posx - data->player.diry * MOVE_SPEED;
		newy = data->player.posy + data->player.dirx * MOVE_SPEED;
	}
	else if (n == 2)
	{
		newx = data->player.posx - data->player.dirx * MOVE_SPEED;
		newy = data->player.posy - data->player.diry * MOVE_SPEED;
	}
	else if (n == 3)
	{
		newx = data->player.posx + data->player.diry * MOVE_SPEED;
		newy = data->player.posy - data->player.dirx * MOVE_SPEED;
	}
	data->player.posx = newx;
	data->player.posy = newy;
}

void	move_cam(t_data *data, int n)
{
	double	rotspeed;
	double	tmp;

	rotspeed = ROT_SPEED * n;
	tmp = data->player.dirx;
	data->player.dirx = data->player.dirx * cos(rotspeed) - data->player.diry * sin(rotspeed);
	data->player.diry = tmp * sin(rotspeed) + data->player.diry * cos(rotspeed);
	tmp = data->player.planex;
	data->player.planex = data->player.planex * cos(rotspeed) - data->player.planey * sin(rotspeed);
	data->player.planey = tmp * sin(rotspeed) + data->player.planey * cos(rotspeed);
}
