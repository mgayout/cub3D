/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 09:22:16 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/18 09:48:59 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D_bonus.h"

t_map	*find_block(t_map *map, int x, int y)
{
	t_map	*tmp;
	int		xmax;
	int		ymax;

	xmax = find_xmax(&map);
	ymax = find_ymax(&map);
	if (x < 0 || y < 0 || x > xmax || y > ymax)
		return (NULL);
	tmp = map;
	while (tmp && (tmp->x != x || tmp->y != y))
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	return (tmp);
}

t_map	*find_player(t_data *data)
{
	t_map	*tmp;

	tmp = data->parse.map;
	while (tmp && tmp->content != 'N' && tmp->content != 'E'
		&& tmp->content != 'S' && tmp->content != 'W')
		tmp = tmp->next;
	return (tmp);
}
