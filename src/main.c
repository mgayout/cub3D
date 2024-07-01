/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 08:14:35 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/01 15:55:46 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	init_data(t_data *data)
{
	t_map	*tmp;
	int	x;
	int	y;

	tmp = data->map;
	x = 0;
	y = 0;
	while (tmp)
	{
		if (tmp->x > x)
			x = tmp->x;
		if (tmp->y > y)
			y = tmp->y;
		tmp = tmp->next;
	}
	data->x = 0;
	data->y = 0;
	data->width = (1500 / x);
	printf("xmax = %d | width = %d\n", x, data->width);
	data->height = (800 / y);
	printf("ymax = %d | height = %d\n", y, data->height);
	init_img(data);
}

void	init_game(t_data *data)
{
	data->mlx_win = mlx_new_window(data->mlx, 1500, 800, "cube3D");
	draw(data);
	//mlx_loop_hook(data->mlx, &draw, data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &press_key, data);
	mlx_hook(data->mlx_win, 17, 0, &free_all, data);
	mlx_loop(data->mlx);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_map	*map;
	
	if (argc < 2 || argc > 3)
		return (0);
	map = NULL;
	data.map = init_map(map, argv[1]);
	print_map(data.map);
	if (data.map != NULL && parse_map(&data))
	{
		data.mlx = mlx_init();
		init_data(&data);
		init_game(&data);
	}
	else
		free_map(&data.map);
}
