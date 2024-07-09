/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:47:46 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/09 13:47:52 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D_bonus.h"

int	print_error(char *str, int i)
{
	while (*str)
		write(2, str++, 1);
	exit(i);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		print_error("Error\nCub3D needs only 1 arg.\n", 1);
	if (ft_strlen(argv[1]) < 4 || (argv[1][ft_strlen(argv[1]) - 4] != '.' || argv[1][ft_strlen(argv[1]) - 3] != 'c'
		|| argv[1][ft_strlen(argv[1]) - 2] != 'u' || argv[1][ft_strlen(argv[1]) - 1] != 'b'))
		print_error("Error\nBad map format.\n", 1);
	if (init_arg(&data, argv[1]))
		return (1);
	init_size(&data);
	if (data.map != NULL && !parse_map(&data))
	{
		data.mlx = mlx_init();
		create_texture(&data);
		data.minimap = false;
		data.door = false;
		init_game(&data);
	}
	else
	{
		free(data.file);
		free_map(&data.map);
		free_texture(&data.texture);
	}
	return (0);
}

int	init_arg(t_data *data, char *file)
{
	char	*buf;
	int		fd;
	int		start;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		print_error("Error\nMap's file is invalid\n", 1);
	data->file = NULL;
	while ((buf = get_next_line(fd)))
	{
		if (!data->file)
			data->file = ft_strdup(buf);
		else
			data->file = ft_strjoin_free(data->file, buf, 1);
		free(buf);
	}
	init_texture(data);
	start = init_walls(data, data->file);
	if (start == -1)
	{
		free(data->file);
		print_error("Error\nMissing texture.\n", 1);
	}
	init_map(data, data->file, start);
	return (0);
}

void	init_size(t_data *data)
{
	data->size.screen_width = 1500;
	data->size.screen_height = 1000;
	xy_max(data);
	block_size(data);
	mini_size(data);
	data->size.moovex = 0;
	data->size.moovey = 0;
}

void	init_game(t_data *data)
{
	data->mlx_win = mlx_new_window(data->mlx, data->size.screen_width, data->size.screen_height, "cub3D");
	draw(data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &press_key, data);
	mlx_hook(data->mlx_win, 17, 0, &free_all, data);
	mlx_loop(data->mlx);
}
