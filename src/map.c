/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:33:03 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/01 14:47:42 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

t_map	*init_map(t_map *map, char *file)
{
	int		fd;
	char	content;
	int		x;
	int		y;

	fd = open(file, O_RDONLY);
	x = 1;
	y = 1;
	while (read(fd, &content, 1))
	{
		if (content == '\n')
		{
			x = 1;
			y += 1;
		}
		else if (content != '\0')
		{
			fill_map(&map, content, x, y);
			x += 1;
		}
	}
	close(fd);
	return (map);
}

void	fill_map(t_map **map, char content, int x, int y)
{
	t_map	*new;
	t_map	*last;

	new = malloc(sizeof(t_map) * 1);
	new->content = content;
	new->x = x;
	new->y = y;
	new->prev = NULL;
	new->next = NULL;
	if (!*map)
		*map = new;
	else
	{
		last = last_map(map);
		last->next = new;
		new->prev = last;
		new->next = NULL;
	}
}

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
		if (y < map->y)
		{
			printf("\n");
			y += 1;
		}
		printf("%c", map->content);
		map = map->next;
	}
	printf("\n");
}
