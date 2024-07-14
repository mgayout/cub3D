/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 08:14:35 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/13 16:35:35 by mgayout          ###   ########.fr       */
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
	if (ft_strlen(argv[1]) < 4 || (argv[1][ft_strlen(argv[1]) - 4] != '.' || argv[1][ft_strlen(argv[1]) - 3] != 'c'
		|| argv[1][ft_strlen(argv[1]) - 2] != 'u' || argv[1][ft_strlen(argv[1]) - 1] != 'b'))
		print_error("Error\nBad map format.\n");
	init_file(&data, argv[1]);
	init_arg(&data);
	init_ray(&data);
	if (check_texture(&data) && check_map(&data))
	{
		data.mlx = mlx_init();
		init_texture(&data);
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
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D");
	set_first_draw(data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &press_key, data);
	mlx_hook(data->mlx_win, 17, 0, &free_all, data);
	mlx_loop(data->mlx);
}
