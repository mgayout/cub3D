/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:33:12 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/09 14:00:26 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	free_all(t_data *data)
{
	free(data->file);
	free_map(&data->map);
	free_texture(&data->texture);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_image(data->mlx, data->texture.player.mlx_img);
	mlx_destroy_image(data->mlx, data->texture.air_player.mlx_img);
	mlx_destroy_image(data->mlx, data->texture.wall.mlx_img);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
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

void	free_texture(t_texture *texture)
{
	if (texture->nwall_path)
		free(texture->nwall_path);
	if (texture->ewall_path)
		free(texture->ewall_path);
	if (texture->swall_path)
		free(texture->swall_path);
	if (texture->wwall_path)
		free(texture->wwall_path);
	if (texture->cwall_color)
		free(texture->cwall_color);
	if (texture->fwall_color)
		free(texture->fwall_color);
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
