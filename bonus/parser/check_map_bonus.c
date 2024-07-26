/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:19:07 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/26 09:35:06 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D_bonus.h"

int	check_map(t_data *data)
{
	if (!valid_char(data))
	{
		printf("Error\nInvalid char\n");
		return (0);
	}
	if (!valid_player(data))
	{
		printf("Error\nInvalid player\n");
		return (0);
	}
	if (!closed_map(data))
	{
		printf("Error\nInvalid map\n");
		return (0);
	}
	return (1);
}

int	valid_char(t_data *data)
{
	t_map	*tmp;

	tmp = data->parse.map;
	while (tmp)
	{
		if (!ft_strchr("10 WENSD", tmp->content))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	valid_player(t_data *data)
{
	t_map	*tmp;
	int		status;

	tmp = data->parse.map;
	status = 0;
	while (tmp)
	{
		if (tmp->content == 'N' || tmp->content == 'E'
			|| tmp->content == 'S' || tmp->content == 'W')
		{
			if (status == 1)
				return (0);
			status++;
		}
		tmp = tmp->next;
	}
	return (status);
}

int	closed_map(t_data *data)
{
	t_map	*new;
	t_map	*tmp;
	int		status;

	new = new_map(data);
	tmp = new;
	status = 1;
	while (tmp)
	{
		if (tmp->content == ' ')
		{
			if (check_closest_block(tmp, tmp->x, tmp->y, "0DNESW"))
			{
				status = 0;
				break ;
			}
		}
		tmp = tmp->next;
	}
	free_map(&new);
	return (status);
}
