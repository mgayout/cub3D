/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:33:12 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/26 08:57:18 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D_bonus.h"

int	free_all(t_data *data)
{
	free_texture(data->parse.texture_path);
	free_map(&data->parse.map);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_image(data->mlx, data->texture.nwall.mlx_img);
	mlx_destroy_image(data->mlx, data->texture.ewall.mlx_img);
	mlx_destroy_image(data->mlx, data->texture.swall.mlx_img);
	mlx_destroy_image(data->mlx, data->texture.wwall.mlx_img);
	mlx_destroy_image(data->mlx, data->texture.door.mlx_img);
	if (data->player.old_posx && data->player.old_posy)
		mlx_destroy_image(data->mlx, data->draw.minimap.mlx_img);
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

void	free_buffer(int **buffer, int n)
{
	int	max;
	int	i;

	if (n == 0)
		max = HEIGHT;
	else
		max = 180;
	i = -1;
	while (++i < max)
		free(buffer[i]);
	free(buffer);
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
