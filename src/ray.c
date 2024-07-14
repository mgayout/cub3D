/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:03:23 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/13 12:03:23 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	init_ray(t_data *data)
{
	t_map	*tmp;
	int		i;

	data->len_rayons = malloc(sizeof(double) * DEGREES);
	if (!data->len_rayons)
		return ;
	i = -1;
	while (++i < DEGREES)
		data->len_rayons[i] = -1;
	tmp = data->parse.map;
	data->ray.xmax = 0;
	data->ray.ymax = 0;
	while (tmp)
	{
		if (tmp->content == 'N' || tmp->content == 'S'
			|| tmp->content == 'E' || tmp->content == 'W')
		{
			init_dir(data, tmp->content);
			data->ray.posx = tmp->x;
			data->ray.posy = tmp->y;
		}
		if (data->ray.xmax < (tmp->x + 1))
			data->ray.xmax = tmp->x + 1;
		if (data->ray.ymax < (tmp->y + 1))
			data->ray.ymax = tmp->y + 1;
		tmp = tmp->next;
	}
	data->ray.width = (WIDTH / data->ray.xmax);
	data->ray.height = (HEIGHT / data->ray.ymax);
}

void	init_dir(t_data *data, char content)
{
	if (content == 'N')
	{
		data->ray.rot = PI / 2;
		data->ray.dirX = cos(data->ray.rot);
		data->ray.dirY = -sin(data->ray.rot);
	}
	else if (content == 'S')
	{
		data->ray.rot = -PI / 2;
		data->ray.dirX = cos(data->ray.rot);
		data->ray.dirY = -sin(data->ray.rot);
	}
	else if (content == 'E')
	{
		data->ray.rot = 0.0;
		data->ray.dirX = cos(data->ray.rot);
		data->ray.dirY = -sin(data->ray.rot);
	}
	else if (content == 'W')
	{
		data->ray.rot = PI;
		data->ray.dirX = cos(data->ray.rot);
		data->ray.dirY = -sin(data->ray.rot);
	}
}
