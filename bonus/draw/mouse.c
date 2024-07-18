/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:33:07 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/18 11:47:16 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D_bonus.h"

int	mouse(int x, int y, t_data *data)
{
	if (x < (WIDTH / 3) && (y > 0 && y < HEIGHT))
	{
		data->key.cam_left = 1;
		data->key.cam_right = 0;
	}
	else if (x > ((WIDTH / 3) * 2) && (y > 0 && y < HEIGHT))
	{
		data->key.cam_left = 0;
		data->key.cam_right = 1;
	}
	else
	{
		data->key.cam_left = 0;
		data->key.cam_right = 0;
	}
	return (1);
}
