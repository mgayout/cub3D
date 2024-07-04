/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:41:19 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/04 19:12:44 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	first_draw(t_data *data)
{
	t_map	*tmp;

	tmp = data->map;
	while (tmp)
	{
		//printf("content = %c\n", tmp->content);
		if (tmp->content == '1')
			mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.wall.mlx_img,
								tmp->x * data->pos.width,
								tmp->y * data->pos.height);
		tmp = tmp->next;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.player.mlx_img,
								data->pos.posx * data->pos.width,
								data->pos.posy * data->pos.height);
	return (0);
}

int	draw(t_data *data, int x, int y)
{
	
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.air.mlx_img,
					(data->pos.posx * data->pos.width) + data->pos.moovex,
					(data->pos.posy * data->pos.height) + data->pos.moovey);
	data->pos.moovex += x;
	data->pos.moovey += y;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->texture.player.mlx_img,
					(data->pos.posx * data->pos.width) + data->pos.moovex,
					(data->pos.posy * data->pos.height) + data->pos.moovey);
	return (0);
}
