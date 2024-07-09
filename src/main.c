/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 08:14:35 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/09 16:23:29 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

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
	if (init_file(&data, argv[1]) || init_arg(&data))
		return (1);
	init_size(&data);
	if (data.map != NULL && !parse_map(&data))
	{
		data.mlx = mlx_init();
		create_texture(&data);
		data.ray = init_ray();
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

int	init_file(t_data *data, char *file)
{
	char	*buf;
	int		fd;

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
	return (0);
}

int	init_arg(t_data *data)
{
	int		start;

	data->texture.nwall_path = NULL;
	data->texture.ewall_path = NULL;
	data->texture.swall_path = NULL;
	data->texture.wwall_path = NULL;
	data->texture.cwall_color = NULL;
	data->texture.fwall_color = NULL;
	start = init_wall(data, data->file);
	if (start == -1)
	{
		free(data->file);
		print_error("Error\nMissing texture.\n", 1);
	}
	data->map = NULL;
	if (data->file[start] != '\0')
		init_map(data, data->file, start);
	return (0);
}

void	init_game(t_data *data)
{
	data->mlx_win = mlx_new_window(data->mlx, data->size.screen_width, data->size.screen_height, "cub3D");
	draw(data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &press_key, data);
	mlx_hook(data->mlx_win, 17, 0, &free_all, data);
	mlx_loop(data->mlx);
}
