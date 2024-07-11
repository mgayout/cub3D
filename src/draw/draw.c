/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:41:19 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/11 16:02:27 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

int	draw(t_data *data)
{
	t_map	*tmp;
	int		posx;
	int		posy;

	tmp = data->parse.map;
	while (tmp)
	{
		if (tmp->content == '1')
		{
			posx = (tmp->x * data->size.block) + ((data->size.block - data->size.wall) / 2);
			posy = (tmp->y * data->size.block) + ((data->size.block - data->size.wall) / 2);
			mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.wall.mlx_img, posx, posy);
		}
		else if (tmp->content == 'N' || tmp->content == 'E' || tmp->content == 'S' || tmp->content == 'W')
		{
			posx = (tmp->x * data->size.block) + ((data->size.block - data->size.player) / 2) + data->size.moovex;
			posy = (tmp->y * data->size.block) + ((data->size.block - data->size.player) / 2) + data->size.moovey;
			mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.player.mlx_img, posx, posy);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	update_player(t_data *data, int x, int y)
{
	t_map	*player;
	int	posx;
	int	posy;
	
	player = find_player(data);
	posx = (player->x * data->size.block) + ((data->size.block - data->size.player) / 2);
	posy = (player->y * data->size.block) + ((data->size.block - data->size.player) / 2);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.air_player.mlx_img, posx + data->size.moovex, posy + data->size.moovey);
	data->size.moovex += x;
	data->size.moovey += y;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.player.mlx_img, posx + data->size.moovex, posy + data->size.moovey);
	return (0);
}

void	update_changes(t_data *data)
{
	//player_moove
	//cam_moove
	
	put_cf_in_buffer(data);
	//put_walls(data);
	init_img(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.mlx_img, 0, 0);
}

void	init_buffer(t_data *data)
{
	int	i;
	
	i = -1;
	data->buffer = malloc(sizeof(int *) * data->size.screen_height);
	while (++i < data->size.screen_height)
		data->buffer[i] = malloc(sizeof(int) * data->size.screen_width);
}

void	put_cf_in_buffer(t_data *data)
{
	int	x;
	int	y;
	
	y = -1;
	init_buffer(data);
	while (++y < (data->size.screen_height / 2))
	{
		x = -1;
		while (++x < data->size.screen_width)
			data->buffer[y][x] = data->texture.c_wall;
	}
	while (++y < data->size.screen_height)
	{
		x = -1;
		while (++x < data->size.screen_width)
			data->buffer[y][x] = data->texture.f_wall;
	}
}

void	init_img(t_data *data)
{
	int	x;
	int	y;
	
	y = -1;
	while (++y < data->size.screen_height)
	{
		x = -1;
		while (++x < data->size.screen_width)
			my_mlx_pixel_put(data, &data->img, x, y, data->buffer[y][x]);
	}
	free_buffer(data);
}

void	my_mlx_pixel_put(t_data *data, t_tex *img, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && x < data->size.screen_width && y > 0 && y < data->size.screen_height)
	{
		dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}
