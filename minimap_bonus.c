/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:48:17 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/09 13:48:19 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D_bonus.h"

int	init_minimap(t_data *data)
{
	if (data->minimap == true)
	{
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.minimap.background.mlx_img, 0, 0);
		draw(data);
		data->minimap = false;
	}
	else
	{
		draw_minimap(data);
		data->minimap = true;
	}
	return (1);
}

int	draw_minimap(t_data *data)
{
	t_map	*player;
	int		posx;
	int		posy;

	mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.minimap.background.mlx_img, 0, 0);
	posx = (5 * data->size.minimap.block) + ((data->size.minimap.block - data->size.minimap.player) / 2);
	posy = (5 * data->size.minimap.block) + ((data->size.minimap.block - data->size.minimap.player) / 2);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.minimap.player.mlx_img, posx, posy);
	posx = (find_player(data)->x * data->size.block) + ((data->size.block - data->size.player) / 2) + data->size.moovex;
	posy = (find_player(data)->y * data->size.block) + ((data->size.block - data->size.player) / 2) + data->size.moovey;
	player = find_block_pixel(data, posx, posy);
	draw_minimap_line(data, player);
	return (0);
}

void	draw_minimap_line(t_data *data, t_map *player)
{
	int		x;
	int		y;
	int 	xmax;
	int		ymax;

	y = 0;
	ymax = 9;
	xmax = 9;
	while (y <= ymax)
	{
		x = 0;
		while (x <= xmax)
		{
			if (find_block_mini(data, player, x, y) == '1')
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.minimap.wall.mlx_img,
										conv_mini_x(data, x), conv_mini_y(data, y));
			x++;
		}
		y++;
	}
}

int	conv_mini_x(t_data *data, int x)
{
	int	posx;

	posx = (data->size.minimap.block * (x + 1));
	return (posx);
}

int	conv_mini_y(t_data *data, int y)
{
	int	posy;

	posy = (data->size.minimap.block * (y + 1));
	return (posy);
}
