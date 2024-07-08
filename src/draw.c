/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:41:19 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/08 17:44:34 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

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
			posx = (tmp->x * data->size.block_width) + ((data->size.block_width - data->size.wall_width) / 2);
			posy = (tmp->y * data->size.block_height) + ((data->size.block_width - data->size.wall_height) / 2);
			mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.wall.mlx_img, posx, posy);
		}
		else if (tmp->content == 'N' || tmp->content == 'E' || tmp->content == 'S' || tmp->content == 'W')
		{
			posx = (tmp->x * data->size.block_width) + ((data->size.block_width - data->size.player_width) / 2);
			posy = (tmp->y * data->size.block_height) + ((data->size.block_width - data->size.player_height) / 2);
			mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.player.mlx_img, posx, posy);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	update_player(t_data *data, int x, int y)
{
	t_map	*tmp;
	int	posx;
	int	posy;
	
	tmp = data->map;
	while (tmp->content != 'N' && tmp->content != 'E' && tmp->content != 'S' && tmp->content != 'W')
		tmp = tmp->next;
	posx = (tmp->x * data->size.block_width) + ((data->size.block_width - data->size.player_width) / 2);
	posy = (tmp->y * data->size.block_height) + ((data->size.block_width - data->size.player_height) / 2);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.air.mlx_img, posx + data->size.moovex, posy + data->size.moovey);
	data->size.moovex += x;
	data->size.moovey += y;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.player.mlx_img, posx + data->size.moovex, posy + data->size.moovey);
	return (0);
}

/*int	draw_minimap(t_data *data)
{
	t_map	*player;
	int		i;

	mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.minimap.background.mlx_img, 0, 0);
	player = search_player();
	i = 0;
	while (i != 5)
	{
		if (i == 0)
			draw_minimap_prev(data, player, i, 4);
		else
			draw_minimap_prev(data, player, i, 9);
		i++;
	}
	i = 0;
	while (i != 5)
	{
		if (i == 0)
			draw_minimap_next(data, player, i, 4);
		else
			draw_minimap_next(data, player, i, 9);
		i++;
	}
	return (0);
}

void	draw_minimap_prev(t_data *data, t_map *player, int status, int max)
{
	t_map	*tmp;
	int 	i;

	tmp = player;
	i = 0;
	while (i != max)
	{
		if (tmp->prev)
		{
			tmp = tmp->prev;
			if (tmp->content == '1')
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.minimap.wall.mlx_img, 0, 0);
		}
		i++;
	}
}

void	draw_minimap_next(t_data *data, t_map *player, int status)
{
	
}

int	clear_minimap(t_data *data)
{
	t_map	*tmp;

	mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.minimap.background.mlx_img, 0, 0);
	tmp = data->map;
	while (tmp)
	{
		if (tmp->content == '1')
			mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.wall.mlx_img,
								tmp->x * data->pos.width,
								tmp->y * data->pos.height);
		tmp = tmp->next;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.player.mlx_img,
					(data->pos.posx * data->pos.width) + data->pos.moovex,
					(data->pos.posy * data->pos.height) + data->pos.moovey);
	return (0);
}*/
