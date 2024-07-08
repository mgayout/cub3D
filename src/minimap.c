/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:37:12 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/08 17:46:13 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	init_minimap(t_data *data)
{
	if (data->minimap == true)
	{
		data->minimap = false;
		//clear_minimap(data);
	}
	else
	{
		//draw_minimap(data);
		data->minimap = true;
	}
	return (1);
}
