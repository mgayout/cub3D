/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:36:11 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/17 15:07:12 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D_bonus.h"

int	check_closest_block(t_map *map, int x, int y, char c)
{
	t_map	*tmp;

	tmp = find_block(map, x, y);
	if (tmp->prev && tmp->prev->content == c)
		return (1);
	if (tmp->next && tmp->next->content == c)
		return (1);
	if (content_up(tmp) == c)
		return (1);
	if (content_down(tmp) == c)
		return (1);
	return (0);
}

char	content_up(t_map *map)
{
	t_map	*tmp;
	int		x;
	int		y;

	tmp = map;
	x = map->x;
	y = map->y;
	if (y == 0)
		return (' ');
	tmp = tmp->prev;
	while (tmp && (tmp->x != x || tmp->y != y - 1))
		tmp = tmp->prev;
	if (!tmp)
		return (' ');
	return (tmp->content);
}

char	content_down(t_map *map)
{
	t_map	*tmp;
	int		x;
	int		y;

	tmp = map;
	x = map->x;
	y = map->y;
	if (y == find_ymax(&map))
		return (' ');
	tmp = tmp->next;
	while (tmp && (tmp->x != x || tmp->y != y + 1))
		tmp = tmp->next;
	if (!tmp)
		return (' ');
	return (tmp->content);
}

t_map	*new_map(t_data *data)
{
	t_map	*new;
	int		xmax;
	int		i;

	new = NULL;
	xmax = find_xmax(&data->parse.map);
	i = 0;
	while (i != xmax + 3)
	{
		if (i == xmax + 2)
			add_map(&new, ' ', 0, 1);
		else
			add_map(&new, ' ', i, 0);
		i++;
	}
	return (new_map2(data, new));
}

t_map	*new_map2(t_data *data, t_map *new)
{
	t_map	*tmp;
	int		xmax;
	int		i;

	tmp = data->parse.map;
	xmax = find_xmax(&data->parse.map);
	i = 1;
	while (tmp)
	{
		add_map(&new, tmp->content, tmp->x + 1, tmp->y + 1);
		if (tmp->x == (xmax - 1))
		{
			add_map(&new, ' ', xmax + 1, i);
			add_map(&new, ' ', 0, i + 1);
			i++;
		}
		tmp = tmp->next;
	}
	i = 0;
	while (i != xmax + 1)
	{
		add_map(&new, ' ', i + 1, find_ymax(&data->parse.map) + 1);
		i++;
	}
	return (new);
}
