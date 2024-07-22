/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:24:00 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/22 11:39:00 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D_bonus.h"

void	init_minimap(t_data *data)
{
	if (!data->player.old_posx && !data->player.old_posy)
	{
		data->draw.minimap.mlx_img = mlx_new_image(data->mlx, 220, 220);
		data->draw.minimap.addr = mlx_get_data_addr(data->draw.minimap.mlx_img,
				&data->draw.minimap.bpp, &data->draw.minimap.line_len,
				&data->draw.minimap.endian);
	}
	init_buff_mini(data);
	draw_minimap(data);
	init_img_minimap(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win,
		data->draw.minimap.mlx_img, 0, 0);
	data->player.old_posx = data->player.posx;
	data->player.old_posy = data->player.posy;
}

void	init_buff_mini(t_data *data)
{
	int	x;
	int	y;
	int	i;
	int	color;

	i = -1;
	data->draw.buff_mini = malloc(sizeof(int *) * 180);
	while (++i < 180)
		data->draw.buff_mini[i] = malloc(sizeof(int) * 180);
	color = create_rgb(0, 0, 0);
	y = -1;
	while (++y < 180)
	{
		x = -1;
		while (++x < 180)
			data->draw.buff_mini[y][x] = color;
	}
}

void	draw_minimap(t_data *data)
{
	t_map	*player;
	t_map	*tmp;
	int		i;
	int		*pos;

	player = find_block(data->parse.map, data->player.posx, data->player.posy);
	pos = malloc(sizeof(int) * 2);
	i = -1;
	while (++i < 81)
	{
		pos[0] = (player->x - 4) + (i % 9);
		pos[1] = (player->y - 4) + (i / 9);
		if (i == 40)
			tmp = player;
		else
			tmp = find_block(data->parse.map, pos[0], pos[1]);
		if (tmp)
			draw_minimap_block(data, tmp, i);
	}
	free(pos);
}

void	init_img_minimap(t_data *data)
{
	int	x;
	int	y;

	y = 19;
	while (++y < 200)
	{
		x = 19;
		while (++x < 200)
			my_mlx_pixel_put(&data->draw.minimap, x, y,
				data->draw.buff_mini[y - 20][x - 20]);
	}
	free_buffer(data->draw.buff_mini, 1);
}
