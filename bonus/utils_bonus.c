/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 09:22:16 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/09 13:49:37 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D_bonus.h"

t_map	*find_block(t_data *data, int x, int y)
{
	t_map	*tmp;

	if (x < 0 || y < 0 || x > data->size.xmax || y > data->size.ymax)
		return (NULL);
	tmp = data->map;
	while (tmp && (tmp->x != x || tmp->y != y))
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	return (tmp);
}

t_map	*find_block_pixel(t_data *data, int posx, int posy)
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
}

t_map	*find_player(t_data *data)
{
	t_map	*tmp;

	tmp = data->map;
	while (tmp && tmp->content != 'N' && tmp->content != 'E' && tmp->content != 'S' && tmp->content != 'W')
		tmp = tmp->next;
	return (tmp);
}

char	find_block_mini(t_data *data, t_map *player, int posx, int posy)
{
	t_map	*tmp;
	int		x;
	int		y;

	if (posx < 0 || posy < 0 || posx > data->size.xmax || posy > data->size.ymax)
		return ('2');
	x = (player->x - 4) + posx;
	y = (player->y - 4) + posy;
	tmp = find_block(data, x, y);
	if (!tmp)
		return ('2');
	return (tmp->content);
}
