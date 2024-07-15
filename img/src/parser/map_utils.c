/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:04:31 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/11 12:04:33 by mgayout          ###   ########.fr       */
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

void	print_map(t_map *map)
{
	int	y;

	y = 0;
	while (map)
	{
		//printf("content = %c | x = %d | y = %d\n", map->content, map->x, map->y);
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
