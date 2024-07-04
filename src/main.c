/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 08:14:35 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/04 19:32:39 by mgayout          ###   ########.fr       */
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
	if (init_arg(&data, argv[1]))
		return (1);
	if (data.map != NULL && !parse_map(&data))
	{
		data.mlx = mlx_init();
		init_texture(&data);
		init_game(&data);
	}
	else
	{
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
	data->texture.nwall_path = NULL;
	data->texture.ewall_path = NULL;
	data->texture.swall_path = NULL;
	data->texture.wwall_path = NULL;
	data->texture.cwall_color = NULL;
	data->texture.fwall_color = NULL;
	start = init_walls(data, data->file);
	if (start == -1)
	{
		free(data->file);
		print_error("Error\nMissing texture.\n", 1);
	}
	init_map(data, data->file, start);
	//print_map(data->map);
	init_data(data);
	free(data->file);
	return (0);
}

void	init_data(t_data *data)
{
	t_map	*tmp;
	int		x;
	int		y;

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
	data->pos.xmax = x + 1;
	data->pos.width = (1500 / data->pos.xmax);
	if (data->pos.width % 2 != 0)
		data->pos.width += 1;
	data->pos.ymax = y + 1;
	data->pos.height = (800 / data->pos.ymax);
	if (data->pos.height % 2 != 0)
		data->pos.height += 1;
	data->pos.moovex = 0;
	data->pos.moovey = 0;
}

void	init_game(t_data *data)
{
	data->mlx_win = mlx_new_window(data->mlx, 1500, 800, "cube3D");
	first_draw(data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &press_key, data);
	mlx_hook(data->mlx_win, 17, 0, &free_all, data);
	mlx_loop(data->mlx);
}
