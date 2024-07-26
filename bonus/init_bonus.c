/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:27:31 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/26 08:57:14 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D_bonus.h"

void	init_data(t_data *data)
{
	init_player(data, &data->player);
	data->texture.c_wall = 0;
	data->texture.f_wall = 0;
	init_ray(&data->ray);
	data->draw.draw_start = 0;
	data->draw.draw_end = 0;
	data->draw.line_height = 0;
	data->key.up = 0;
	data->key.right = 0;
	data->key.down = 0;
	data->key.left = 0;
	data->key.cam_left = 0;
	data->key.cam_right = 0;
	data->key.minimap = 0;
	data->key.door = 0;
}

void	init_player(t_data *data, t_player *player)
{
	t_map	*tmp;

	tmp = find_player(data);
	player->dir = tmp->content;
	player->posx = tmp->x + 0.5;
	player->posy = tmp->y + 0.5;
	player->old_posx = 0;
	player->old_posy = 0;
	if (player->dir == 'N' || player->dir == 'S')
		init_ns_dir(player);
	else
		init_ew_dir(player);
}

void	init_ray(t_ray *ray)
{
	ray->camera = 0;
	ray->ray_dirx = 0;
	ray->ray_diry = 0;
	ray->delta_distx = 0;
	ray->delta_disty = 0;
	ray->side_distx = 0;
	ray->side_disty = 0;
	ray->stepx = 0;
	ray->stepy = 0;
	ray->mapx = 0;
	ray->mapy = 0;
	ray->hit_side = 0;
	ray->perp_wall_dist = 0;
	ray->door = 0;
}

void	init_ns_dir(t_player *player)
{
	if (player->dir == 'N')
	{
		player->dirx = 0.01;
		player->diry = -1.01;
		player->planex = 0.66;
		player->planey = 0.0;
	}
	else if (player->dir == 'S')
	{
		player->dirx = 0.01;
		player->diry = 1.01;
		player->planex = -0.66;
		player->planey = 0.0;
	}
}

void	init_ew_dir(t_player *player)
{
	if (player->dir == 'E')
	{
		player->dirx = 1.01;
		player->diry = 0.01;
		player->planex = 0;
		player->planey = 0.66;
	}
	else if (player->dir == 'W')
	{
		player->dirx = -1.01;
		player->diry = 0.01;
		player->planex = 0;
		player->planey = -0.66;
	}
}
