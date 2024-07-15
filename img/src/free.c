/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:33:12 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/13 16:40:30 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	free_all(t_data *data)
{
	free_texture(data->parse.texture_path);
	free_map(&data->parse.map);
	free(data->len_rayons);
	//free_intab(data->tab_walls, (data->ray.ymax + 1));
	//free_buffer(data, data->buffer);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_image(data->mlx, data->img.mlx_img);
	mlx_destroy_image(data->mlx, data->texture.nwall.mlx_img);
	mlx_destroy_image(data->mlx, data->texture.ewall.mlx_img);
	mlx_destroy_image(data->mlx, data->texture.swall.mlx_img);
	mlx_destroy_image(data->mlx, data->texture.wwall.mlx_img);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

void	free_texture(char **texture_path)
{
	int	i;

	i = 0;
	while (i != 7)
	{
		if (texture_path[i])
			free(texture_path[i]);
		i++;
	}
	free(texture_path);
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

void	free_buffer(t_data *data)
{
	int	i;

	i = -1;
	while (++i < HEIGHT)
		free(data->buffer[i]);
	free(data->buffer);
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

void	free_intab(int **i, int n)
{
	int	j;

	j = -1;
	while (++j < n)
		free(i[j]);
	free(i);
}