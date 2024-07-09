/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:16:35 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/09 17:18:09 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	*init_ray(void)
{
	int	*ray;
	int	dis;
	int	i;

	ray = malloc(sizeof(int) * 60);
	dis = 250;
	i = 0;
	while (i != 20)
	{
		ray[i] = dis;
		dis -= 2;
		i++;
	}
	while (i != 30)
	{
		ray[i] = dis;
		dis -= 1;
		i++;
	}
	while (i != 30)
	{
		ray[i] = dis;
		dis += 1;
		i++;
	}
	while (i != 60)
	{
		ray[i] = dis;
		dis += 2;
		i++;
	}
	return (ray);
}

void	test(t_data *data)
{
	int	line;
	int	pitch;

	line = 100;
}