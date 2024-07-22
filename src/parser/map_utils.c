/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:04:31 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/22 12:28:02 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

t_map	*last_map(t_map **map)
{
	t_map	*last;

	last = *map;
	while (last->next)
		last = last->next;
	return (last);
}

int	find_xmax(t_map **map)
{
	t_map	*tmp;
	int		x;

	tmp = *map;
	x = 0;
	while (tmp)
	{
		if (x < tmp->x)
			x = tmp->x;
		tmp = tmp->next;
	}
	return (x + 1);
}

int	find_ymax(t_map **map)
{
	t_map	*tmp;
	int		y;

	tmp = *map;
	y = 0;
	while (tmp)
	{
		if (y < tmp->y)
			y = tmp->y;
		tmp = tmp->next;
	}
	return (y + 1);
}
