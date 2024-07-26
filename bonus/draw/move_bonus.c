/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:23:06 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/26 08:58:35 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D_bonus.h"

void	move(t_data *data)
{
	if (data->key.up != 0)
	{
		move_playerx(data, 0);
		move_playery(data, 0);
	}
	if (data->key.right != 0)
	{
		move_playerx(data, 1);
		move_playery(data, 1);
	}
	if (data->key.down != 0)
	{
		move_playerx(data, 2);
		move_playery(data, 2);
	}
	if (data->key.left != 0)
	{
		move_playerx(data, 3);
		move_playery(data, 3);
	}
	if (data->key.cam_left != 0)
		move_cam(data, -1);
	if (data->key.cam_right != 0)
		move_cam(data, 1);
}

void	move_playerx(t_data *data, int n)
{
	double	newx;

	if (n == 0)
		newx = data->player.posx + data->player.dirx * MOVE_SPEED;
	else if (n == 1)
		newx = data->player.posx - data->player.diry * MOVE_SPEED;
	else if (n == 2)
		newx = data->player.posx - data->player.dirx * MOVE_SPEED;
	else if (n == 3)
		newx = data->player.posx + data->player.diry * MOVE_SPEED;
	if (newx > 1 && newx <= ((double)data->parse.xmax - 1)
		&& !check_wall(data, newx, 0))
		data->player.posx = newx;
}

void	move_playery(t_data *data, int n)
{
	double	newy;

	if (n == 0)
		newy = data->player.posy + data->player.diry * MOVE_SPEED;
	else if (n == 1)
		newy = data->player.posy + data->player.dirx * MOVE_SPEED;
	else if (n == 2)
		newy = data->player.posy - data->player.diry * MOVE_SPEED;
	else if (n == 3)
		newy = data->player.posy - data->player.dirx * MOVE_SPEED;
	if (newy > 1 && newy <= ((double)data->parse.ymax - 1)
		&& !check_wall(data, newy, 1))
		data->player.posy = newy;
}

void	move_cam(t_data *data, int n)
{
	double	rotspeed;
	double	tmp;

	rotspeed = ROT_SPEED * n;
	tmp = data->player.dirx;
	data->player.dirx = data->player.dirx * cos(rotspeed)
		- data->player.diry * sin(rotspeed);
	data->player.diry = tmp * sin(rotspeed) + data->player.diry * cos(rotspeed);
	tmp = data->player.planex;
	data->player.planex = data->player.planex * cos(rotspeed)
		- data->player.planey * sin(rotspeed);
	data->player.planey = tmp * sin(rotspeed)
		+ data->player.planey * cos(rotspeed);
}
