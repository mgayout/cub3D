/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:47:03 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/09 13:47:04 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D_bonus.h"

int	draw(t_data *data)
{
	t_map	*tmp;
	int		posx;
	int		posy;

	tmp = data->map;
	while (tmp)
	{
		if (tmp->content == '1')
		{
			posx = (tmp->x * data->size.block) + ((data->size.block - data->size.wall) / 2);
			posy = (tmp->y * data->size.block) + ((data->size.block - data->size.wall) / 2);
			mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.wall.mlx_img, posx, posy);
		}
		if (tmp->content == 'D')
		{
			posx = (tmp->x * data->size.block) + ((data->size.block - data->size.wall) / 2);
			posy = (tmp->y * data->size.block) + ((data->size.block - data->size.wall) / 2);
			mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.door.mlx_img, posx, posy);
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
