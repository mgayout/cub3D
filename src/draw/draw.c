/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:30:14 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/13 16:30:14 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

void	set_first_draw(t_data *data)
{
	put_cf_in_buffer(data);
	//put_walls(data);
	init_img(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.mlx_img, 0, 0);
}

void	update_changes(t_data *data)
{
	int	i;

	//player_moove
	//cam_moove
	raycasting(data);
	i = -1;
	while (++i < DEGREES)
		printf("%d = %f\n", i, data->len_rayons[i]);

	put_cf_in_buffer(data);
	//put_walls(data);
	init_img(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.mlx_img, 0, 0);
}
