/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:38:48 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/01 15:55:01 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	press_key(int key, t_data *data)
{
	if (key == XK_Escape)
		free_all(data);
	if (key == XK_w)
		data->y -= 5;
	if (key == XK_a)
		data->x -= 5;
	if (key == XK_d)
		data->x += 5;
	if (key == XK_s)
		data->y += 5;
	//mlx_destroy_image(data->mlx, data->img.player.mlx_img);
	draw(data);
	return (0);
}