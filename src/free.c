/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:33:12 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/02 15:45:01 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	free_all(t_data *data)
{
	free_map(&data->map);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_image(data->mlx, data->img.air.mlx_img);
	mlx_destroy_image(data->mlx, data->img.player.mlx_img);
	mlx_destroy_image(data->mlx, data->img.wall.mlx_img);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data->img.c_wall);
	free(data->img.e_wall);
	free(data->img.f_wall);
	free(data->img.w_wall);
	free(data->img.n_wall);
	free(data->img.s_wall);
	exit(0);
}

void	free_map(t_map **map)
{
	t_map	*tmp;
	
	while (*map)
	{
		tmp = *map;
		*map = (*map)->next;
		free(tmp);
	}
}

void	free_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
