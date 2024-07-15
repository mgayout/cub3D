/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:33:32 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/15 14:15:38 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

void	calculate_delta(t_data *data)
{
	if (data->ray.ray_dirx == 0)
		data->ray.delta_distx = 1e30;
	else
		data->ray.delta_distx = fabs(1 / data->ray.ray_dirx);
	if (data->ray.ray_diry == 0)
		data->ray.delta_disty = 1e30;
	else
		data->ray.delta_disty = fabs(1 / data->ray.ray_diry);
}

void	calculate_side_dist(t_data *data)
{
	if (data->ray.ray_dirx < 0)
	{
		data->ray.stepx = -1;
		data->ray.side_distx = (data->player.posx - data->ray.mapx)
			* data->ray.delta_distx;
	}
	else
	{
		data->ray.stepx = 1;
		data->ray.side_distx = (data->ray.mapx + 1.0 - data->player.posx)
			* data->ray.delta_distx;
	}
	if (data->ray.ray_diry < 0)
	{
		data->ray.stepy = -1;
		data->ray.side_disty = (data->player.posy - data->ray.mapy)
			* data->ray.delta_disty;
	}
	else
	{
		data->ray.stepy = 1;
		data->ray.side_disty = (data->ray.mapy + 1.0 - data->player.posy)
			* data->ray.delta_disty;
	}
}

void	exec_dda(t_data *data, int x)
{
	bool	hit;

	(void)x;
	hit = false;
	while (hit == false)
	{
		if (data->ray.side_distx < data->ray.side_disty)
		{
			data->ray.side_distx += data->ray.delta_distx;
			data->ray.mapx += data->ray.stepx;
			data->ray.hit_side = 0;
		}
		else
		{
			data->ray.side_disty += data->ray.delta_disty;
			data->ray.mapy += data->ray.stepy;
			data->ray.hit_side = 1;
		}
		//printf("mapx = %d | mapy = %d\n", data->ray.mapx, data->ray.mapy);
		if (find_block(data, data->ray.mapx, data->ray.mapy)->content == '1')
			hit = true;
	}
}

void	calc_perp_wall_dist(t_data *data)
{
	if (data->ray.hit_side == 0)
		data->ray.perp_wall_dist = (data->ray.side_distx
				- data->ray.delta_distx);
	else
		data->ray.perp_wall_dist = (data->ray.side_disty
				- data->ray.delta_disty);
}

void	calc_height_wall(t_data *data)
{
	data->draw.line_height = (int)(HEIGHT / data->ray.perp_wall_dist);
	data->draw.draw_start = -data->draw.line_height / 2 + HEIGHT / 2;
	if (data->draw.draw_start < 0)
		data->draw.draw_start = 0;
	data->draw.draw_end = data->draw.line_height / 2 + HEIGHT / 2;
	if (data->draw.draw_end >= HEIGHT)
		data->draw.draw_end = HEIGHT - 1;
}
