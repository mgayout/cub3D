/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:38:48 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/08 18:02:55 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	press_key(int key, t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (key == XK_Escape)
		free_all(data);
	//else if (key == XK_m)
		//return (init_minimap(data));
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

	tmp = data->map;
	while (tmp->content != 'N' && tmp->content != 'E' && tmp->content != 'S' && tmp->content != 'W')
		tmp = tmp->next;
	up = (tmp->y * data->size.block_height) + ((data->size.block_width - data->size.player_height) / 2) + data->size.moovey;
	right = ((tmp->x + 1) * data->size.block_width) + ((data->size.block_width - data->size.player_width) / 2) + data->size.moovex;
	down = ((tmp->y + 1) * data->size.block_height) - ((data->size.block_width - data->size.player_height) / 2) + data->size.moovey;
	left = (tmp->x * data->size.block_width) + ((data->size.block_width - data->size.player_width) / 2) + data->size.moovex;
	if (check_top_right(data, up, right))
		return (1);
	else if (check_bottom_right(data, up, right))
		return (1);
	else if (check_bottom_left(data, up, right))
		return (1);
	else if (check_top_left(data, up, right))
		return (1);
	return (0);
}

int	check_top_right(t_data *data, int up, int right)
{
	
}

int	check_bottom_right(t_data *data, int down, int right)
{
	
}

int	check_bottom_left(t_data *data, int down, int left)
{
	
}

int	check_top_left(t_data *data, int up, int left)
{
	
}
