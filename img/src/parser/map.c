/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:33:03 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/11 11:40:37 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

int	init_map(t_data *data, char *file, int start)
{
	t_map	*map;
	int		x;
	int		y;

	map = NULL;
	x = 0;
	y = 0;
	while (file[start] == ' ' || file[start] == '\n')
		start++;
	while (file[start] != '\n')
		start--;
	while (file[start++])
	{
		x = start;
		while (file[start] != '\n' && file[start] != '\0')
		{
			if (file[start] != '\n')
				add_map(&map, file[start], start - x, y);
			start++;
		}
		y++;
	}
	data->parse.map = map;
	return (0);
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
