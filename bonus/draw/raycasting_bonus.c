/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 08:58:28 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/26 08:58:28 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D_bonus.h"

void	init_tex_dir(t_data *data)
{
	if (data->ray.door)
		data->draw.wall.select_tex = data->texture.door;
	else if (data->ray.hit_side == 1 && data->ray.ray_diry < 0)
		data->draw.wall.select_tex = data->texture.nwall;
	else if (data->ray.hit_side == 1 && data->ray.ray_diry >= 0)
		data->draw.wall.select_tex = data->texture.swall;
	else if (data->ray.hit_side == 0 && data->ray.ray_dirx >= 0)
	{
		if (data->player.dir == 'N' || data->player.dir == 'E')
			data->draw.wall.select_tex = data->texture.ewall;
		else
			data->draw.wall.select_tex = data->texture.wwall;
	}
	else if (data->ray.hit_side == 0 && data->ray.ray_dirx < 0)
	{
		if (data->player.dir == 'N' || data->player.dir == 'E')
			data->draw.wall.select_tex = data->texture.wwall;
		else
			data->draw.wall.select_tex = data->texture.ewall;
	}
}

void	calc_wall_x(t_data *data)
{
	if (data->ray.hit_side == 0)
		data->draw.wall.wall_x = data->player.posy + data->ray.perp_wall_dist
			* data->ray.ray_diry;
	else
		data->draw.wall.wall_x = data->player.posx + data->ray.perp_wall_dist
			* data->ray.ray_dirx;
	data->draw.wall.wall_x -= floor((data->draw.wall.wall_x));
}

void	calc_x_coord_tex(t_data *data)
{
	data->draw.wall.tex_x = (int)(data->draw.wall.wall_x
			* (double)data->draw.wall.select_tex.tex_width);
	if (data->ray.hit_side == 0 && data->ray.ray_dirx > 0)
		data->draw.wall.tex_x = data->draw.wall.select_tex.tex_width
			- data->draw.wall.tex_x - 1;
	if (data->ray.hit_side == 1 && data->ray.ray_diry < 0)
		data->draw.wall.tex_x = data->draw.wall.select_tex.tex_width
			- data->draw.wall.tex_x - 1;
}

void	color_x_stripe(t_data *data, int x)
{
	double	step;
	double	tex_pos;
	int		y;
	int		color;

	step = 1.0 * data->draw.wall.select_tex.tex_height / data->draw.line_height;
	tex_pos = (data->draw.draw_start - HEIGHT / 2 + data->draw.line_height / 2)
		* step;
	y = data->draw.draw_start - 1;
	while (++y < data->draw.draw_end)
	{
		data->draw.wall.tex_y = (int)tex_pos
			& (data->draw.wall.select_tex.tex_height - 1);
		tex_pos += step;
		color = (*(int *)(data->draw.wall.select_tex.addr + (4
						* data->draw.wall.select_tex.tex_width
						* (int)data->draw.wall.tex_y)
					+ (4 * (int)data->draw.wall.tex_x)));
		data->draw.buffer[y][x] = color;
	}
}
