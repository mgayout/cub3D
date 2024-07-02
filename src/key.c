/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:38:48 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/02 12:50:02 by mgayout          ###   ########.fr       */
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
	else if (key == XK_w || key == XK_Up)
		y -= (data->pos.height / 2);
	else if (key == XK_a || key == XK_Left)
		x -= (data->pos.width / 2);
	else if (key == XK_d || key == XK_Right)
		x += (data->pos.width / 2);
	else if (key == XK_s || key == XK_Down)
		y += (data->pos.height / 2);
	else
		return (0);
	if (walled(data, x, y))
		return (0);
	draw(data, x, y);
	return (0);
}

int	walled(t_data *data, int x, int y)
{
	t_map	*tmp;
	int		*pos;
	
	tmp = data->map;
	if (x > 0 || y > 0)
		pos = moove_up(data, x, y);
	else if (x < 0 || y < 0)
		pos = moove_down(data, x, y);
	//printf("x = %d | y = %d\n", pos[0], pos[1]);
	//printf("x2 = %d | y2 = %d\n", pos[2], pos[3]);
	//printf("x3 = %d | y3 = %d\n", pos[4], pos[5]);
	//printf("x4 = %d | y4 = %d\n", pos[6], pos[7]);
	while (tmp && pos)
	{
		if (((tmp->x == pos[0] && tmp->y == pos[1]) || (tmp->x == pos[2] && tmp->y == pos[3])
			|| (tmp->x == pos[4] && tmp->y == pos[5]) || (tmp->x == pos[6] && tmp->y == pos[7]))
			&& tmp->content == '1')
		{
			free(pos);
			return (1);
		}
		tmp = tmp->next;
	}
	free(pos);
	return (0);
}

int	*moove_up(t_data *data, int x, int y)
{
	int	*pos;

	pos = malloc(sizeof(int) * 8);
	if (!pos)
		return (NULL);
	if (((data->pos.moovex + x) % data->pos.width) != 0)
	{
		//printf("moove up 1\n");
		pos[0] = (((data->pos.moovex + x) + (data->pos.posx * data->pos.width)) / data->pos.width);
		pos[2] = pos[0] + 1;
		pos[4] = (((data->pos.moovex + x) + (data->pos.posx * data->pos.width)) / data->pos.width);
		pos[6] = pos[4] + 1;;
	}
	else
	{
		//printf("moove up 2\n");
		pos[0] = (((data->pos.moovex + x) + (data->pos.posx * data->pos.width)) / data->pos.width);
		pos[2] = (((data->pos.moovex + x) + (data->pos.posx * data->pos.width)) / data->pos.width);
		pos[4] = (((data->pos.moovex + x) + (data->pos.posx * data->pos.width)) / data->pos.width);
		pos[6] = (((data->pos.moovex + x) + (data->pos.posx * data->pos.width)) / data->pos.width);
	}
	if (((data->pos.moovey + y) % data->pos.height) != 0)
	{
		//printf("moove up 3\n");
		pos[1] = (((data->pos.moovey + y) + (data->pos.posy * data->pos.height)) / data->pos.height);
		pos[3] = pos[1] + 1;
		pos[5] = pos[1] + 1;
		pos[7] = (((data->pos.moovey + y) + (data->pos.posy * data->pos.height)) / data->pos.height);
	}
	else
	{
		//printf("moove up 4\n");
		pos[1] = (((data->pos.moovey + y) + (data->pos.posy * data->pos.height)) / data->pos.height);
		pos[3] = (((data->pos.moovey + y) + (data->pos.posy * data->pos.height)) / data->pos.height);
		pos[5] = (((data->pos.moovey + y) + (data->pos.posy * data->pos.height)) / data->pos.height);
		pos[7] = (((data->pos.moovey + y) + (data->pos.posy * data->pos.height)) / data->pos.height);
	}
	return (pos);
}

int	*moove_down(t_data *data, int x, int y)
{
	int	*pos;

	pos = malloc(sizeof(int) * 8);
	if (!pos)
		return (NULL);
	if (((data->pos.moovex + x) % data->pos.width) != 0)
	{
		//printf("moove down 1\n");
		pos[0] = (((data->pos.moovex + x) + (data->pos.posx * data->pos.width)) / data->pos.width);
		pos[2] = pos[0] + 1;
		pos[4] = (((data->pos.moovex + x) + (data->pos.posx * data->pos.width)) / data->pos.width);
		pos[6] = pos[4] + 1;
	}
	else
	{
		//printf("moove down 2\n");
		pos[0] = (((data->pos.moovex + x) + (data->pos.posx * data->pos.width)) / data->pos.width);
		pos[2] = (((data->pos.moovex + x) + (data->pos.posx * data->pos.width)) / data->pos.width);
		pos[4] = (((data->pos.moovex + x) + (data->pos.posx * data->pos.width)) / data->pos.width);
		pos[6] = (((data->pos.moovex + x) + (data->pos.posx * data->pos.width)) / data->pos.width);
	}
	if (((data->pos.moovey + y) % data->pos.height) != 0)
	{
		//printf("moove down 3\n");
		pos[1] = (((data->pos.moovey + y) + (data->pos.posy * data->pos.height)) / data->pos.height);
		pos[3] = pos[1] + 1;
		pos[5] = pos[1] + 1;
		pos[7] = (((data->pos.moovey + y) + (data->pos.posy * data->pos.height)) / data->pos.height);
	}
	else
	{
		//printf("moove down 4\n");
		pos[1] = (((data->pos.moovey + y) + (data->pos.posy * data->pos.height)) / data->pos.height);
		pos[3] = (((data->pos.moovey + y) + (data->pos.posy * data->pos.height)) / data->pos.height);
		pos[5] = (((data->pos.moovey + y) + (data->pos.posy * data->pos.height)) / data->pos.height);
		pos[7] = (((data->pos.moovey + y) + (data->pos.posy * data->pos.height)) / data->pos.height);
	}
	return (pos);
}
