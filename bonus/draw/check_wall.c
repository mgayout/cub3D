/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:02:14 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/18 12:50:26 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D_bonus.h"

int	check_wall(t_data *data, int newpos, int n)
{
	t_map	*tmp;
	int		x;
	int		y;

	if (n == 0)
	{
		x = newpos;
		y = (int)data->player.posy;
	}
	else
	{
		x = (int)data->player.posx;
		y = newpos;
	}
	tmp = find_block(data->parse.map, x, y);
	/*printf("x = %d | y = %d | content = %c\n", tmp->x, tmp->y, tmp->content);
	if (data->key.door)
		printf("door true\n");
	if (!data->key.door)
		printf("door false\n");*/
	if (tmp->content == '1' || (data->key.door && tmp->content == 'D'))
		return (1);
	return (0);
}
