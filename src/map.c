/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:33:03 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/05 16:30:17 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	init_map(t_data *data, char *file, int start)
{
	t_map	*map;
	char	**split_arg;
	int		i;
	int		x;

	map = NULL;
	split_arg = ft_split(file, '\n');
	i = 0;
	if (!split_arg[start])
	{
		data->map = NULL;
		free_tab(split_arg);
		return ;
	}
	while (!check_line(split_arg[start]))
		start++;
	while (split_arg[start + i])
	{
		x = 0;
		while (split_arg[start + i][x])
		{
			add_map(&map, split_arg[start + i][x], x, i);
			x++;
		}
		i++;
	}
	free_tab(split_arg);
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
	t_map	*ptr;
	int		x;
	
	tmp = *map;
	while (tmp)
	{
		//printf("%c\n", tmp->content);
		if (((tmp->next && tmp->next->y == tmp->y + 1) || !tmp->next) && tmp->x != data->pos.xmax)
		{
			x = tmp->x + 1;
			ptr = tmp->next;
			while (x < data->pos.xmax)
			{
				add_map_space(tmp, x, tmp->y);
				//printf("%c", tmp->content);
				tmp = tmp->next;
				x++;
			}
			if (ptr)
				ptr->prev = tmp;
			tmp->next = ptr;
		}
		//printf("%c\n", tmp->content);
		tmp = tmp->next;
	}
}

void	add_map_space(t_map *map, int x, int y)
{
	t_map	*new;

	new = malloc(sizeof(t_map) * 1);
	new->content = ' ';
	new->x = x;
	new->y = y;
	new->prev = map;
	new->next = NULL;
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
