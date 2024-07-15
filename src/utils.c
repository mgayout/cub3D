/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 09:22:16 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/15 11:50:53 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

t_map	*find_block(t_data *data, int x, int y)
{
	t_map	*tmp;
	int		xmax;
	int		ymax;

	xmax = find_xmax(&data->parse.map);
	ymax = find_ymax(&data->parse.map);
	if (x < 0 || y < 0 || x > xmax || y > ymax)
		return (NULL);
	tmp = data->parse.map;
	while (tmp && (tmp->x != x || tmp->y != y))
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	return (tmp);
}

/*t_map	*find_block_pixel(t_data *data, int posx, int posy)
{
	int	x;
	int	y;
	
	x = 0;
	y = 0;
	while (posx >= data->size.block)
	{
		posx -= data->size.block;
		x++;
	}
	while (posy >= data->size.block)
	{
		posy -= data->size.block;
		y++;
	}
	return (find_block(data, x, y));
}*/

t_map	*find_player(t_data *data)
{
	t_map	*tmp;

	tmp = data->parse.map;
	while (tmp && tmp->content != 'N' && tmp->content != 'E' && tmp->content != 'S' && tmp->content != 'W')
		tmp = tmp->next;
	return (tmp);
}
