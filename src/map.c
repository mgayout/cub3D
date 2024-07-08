/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:33:03 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/08 16:24:48 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	init_map(t_data *data, char *file, int start)
{
	t_map	*map;
	int		x;
	int		y;

	map = NULL;
	x = 0;
	y = 0;
	if (file[start] == '\0')
	{
		printf("1\n");
		data->map = map;
		return ;
	}
	while (file[start] == ' ' || file[start] == '\n')
		start++;
	while (file[start] != '\n')
		start--;
	while (file[start++])
	{
		x = start;
		while (file[start] != '\n' && file[start] != '\0')
		{
			//printf("file[start] = %c | x : %d | y : %d\n", file[start], start - x, y);
			if (file[start] != '\n')
				add_map(&map, file[start], start - x, y);
			start++;
		}
		y++;
	}
	data->map = map;
}

void	add_map(t_map **map, char content, int x, int y)
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

void	fill_map(t_data *data, t_map **map)
{
	t_map	*tmp;
	int		x;
	
	tmp = *map;
	while (tmp)
	{
		if (((tmp->next && tmp->next->y > tmp->y) || !tmp->next) && tmp->x != data->size.xmax)
		{
			x = tmp->x + 1;
			while (x < data->size.xmax)
			{
				add_map_space(tmp, ' ', x, tmp->y);
				tmp = tmp->next;
				x++;
			}
		}
		if (tmp->next && tmp->next->y > tmp->y + 1)
			add_map_space(tmp, ' ', 0, tmp->y + 1);
		tmp = tmp->next;
	}
}

void	add_map_space(t_map *map, char c, int x, int y)
{
	t_map	*new;
	t_map	*next;

	new = malloc(sizeof(t_map) * 1);
	next = map->next;
	new->content = c;
	new->x = x;
	new->y = y;
	new->prev = map;
	new->next = next;
	map->next = new;
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
