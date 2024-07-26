/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 08:14:35 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/26 09:06:46 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	print_error(char *str)
{
	while (*str)
		write(2, str++, 1);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		print_error("Error\nCub3D needs only 1 arg.\n");
	if (ft_strlen(argv[1]) < 4 || (argv[1][ft_strlen(argv[1]) - 4] != '.'
		|| argv[1][ft_strlen(argv[1]) - 3] != 'c'
		|| argv[1][ft_strlen(argv[1]) - 2] != 'u'
		|| argv[1][ft_strlen(argv[1]) - 1] != 'b'))
		print_error("Error\nBad map format.\n");
	init_file(&data, argv[1]);
	init_arg(&data);
	if (check_texture(&data) && check_map(&data))
	{
		data.mlx = mlx_init();
		init_game(&data);
	}
	else
	{
		free_texture(data.parse.texture_path);
		free_map(&data.parse.map);
	}
	return (0);
}

void	init_game(t_data *data)
{
	init_data(data);
	init_texture(data);
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D");
	draw(data);
	key_signal(data);
	mlx_loop_hook(data->mlx, &update, data);
	mlx_loop(data->mlx);
}

int	update(t_data *data)
{
	if (data->key.up || data->key.right || data->key.down || data->key.left
		|| data->key.cam_left || data->key.cam_right)
	{
		move(data);
		draw(data);
	}
	return (1);
}
