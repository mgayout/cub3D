/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:04:31 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/26 08:57:37 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D_bonus.h"

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

void	print_map(t_map *map)
{
	int	y;

	y = 0;
	while (map)
	{
		while (y < map->y)
		{
			printf("\n");
			y += 1;
		}
		printf("%c", map->content);
		map = map->next;
	}
	printf("\n");
}
