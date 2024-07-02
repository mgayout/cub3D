/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 08:14:35 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/02 18:01:21 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	init_arg(t_data *data, char *file)
{
	data->img.n_wall = NULL;
	data->img.e_wall = NULL;
	data->img.s_wall = NULL;
	data->img.w_wall = NULL;
	data->img.c_wall = NULL;
	data->img.f_wall = NULL;
	if (init_walls(data, file))
		return (1);
	init_map(data, file);
	//print_map(data->map);
	init_data(data);
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
		if (tmp->content == 'P')
		{
			data->pos.posx = tmp->x;
			data->pos.posy = tmp->y;
		}
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

int	main(int argc, char **argv)
{
	t_data	data;
	
	if (argc < 2 || argc > 3)
		return (0);
	if (argv[1][ft_strlen(argv[1]) - 4] != '.' || argv[1][ft_strlen(argv[1]) - 3] != 'c'
		|| argv[1][ft_strlen(argv[1]) - 2] != 'u' || argv[1][ft_strlen(argv[1]) - 1] != 'b')
		return (0);
	if (init_arg(&data, argv[1]))
		return (0);
	if (data.map != NULL && parse_map(&data))
	{
		data.mlx = mlx_init();
		init_img(&data);
		init_game(&data);
	}
	else
	{
		free_map(&data.map);
		free_img(&data.img);
	}
	return (0);
}
