/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 08:14:35 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/01 12:55:19 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	init_game(t_data *data)
{
	int	width;
	int height;
	
	width = (data->width - 1) * 32;
	height = (data->height - 1) * 32;
	init_img(data);
	data->mlx_win = mlx_new_window(data->mlx, width, height, "cube3D");
	draw(data);
	//mlx_loop_hook(data->mlx, &draw, data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, &press_key, data);
	mlx_hook(data->mlx_win, 17, 0, &free_all, data);
	mlx_loop(data->mlx);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_map	*map;
	
	if (argc < 2 || argc > 3)
		return (0);
	data.mlx = mlx_init();
	map = NULL;
	data.map = init_map(map, argv[1]);
	data.width = last_map(&data.map)->x + 1;
	data.height = last_map(&data.map)->y + 1;
	//data.pixel_x = data.height / 64;
	//data.pixel_y = data.width / 64;
	print_map(data.map);
	init_game(&data);
}
