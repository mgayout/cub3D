/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:19:07 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/02 12:14:32 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	parse_map(t_data *data)
{
	//if (closed_map(data))
		//return (0);
	if (valid_char(data))
		return (0);
	return (1);
}

int	valid_char(t_data *data)
{
	t_map	*tmp;

	tmp = data->map;
	while (tmp)
	{
		if (!ft_strchr("10 PWENS", tmp->content))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
