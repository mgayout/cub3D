/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:19:07 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/09 15:10:14 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

int	parse_map(t_data *data)
{
	fill_map(data, &data->map);
	if (!valid_char(data))
	{
		printf("Error\nInvalid char\n");
		return (1);
	}
	if (!valid_color(data->texture.cwall_color) || !valid_color(data->texture.fwall_color))
	{
		printf("Error\nInvalid color\n");
		return (1);
	}
	if (!valid_player(data))
	{
		printf("Error\nInvalid player\n");
		return (1);
	}
	if (!closed_map(data))
	{
		printf("Error\nInvalid map\n");
		return (1);
	}
	return (0);
}

int	valid_char(t_data *data)
{
	t_map	*tmp;

	tmp = data->map;
	while (tmp)
	{
		if (!ft_strchr("10 WENS", tmp->content))
		{
			//printf("content = %c\n", tmp->content);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	valid_color(char *str)
{
	char	**arg;
	int		i;
	
	arg = ft_split(str, ',');
	i = 0;
	while (arg[i])
	{
		if (ft_atoi_color(arg[i]) > 255 || ft_atoi_color(arg[i]) < 0)
		{
			free_tab(arg);
			return (0);
		}
		i++;
	}
	free_tab(arg);
	return (1);
}

int	valid_player(t_data *data)
{
	t_map	*tmp;
	int		status;

	tmp = data->map;
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
			if ((tmp->prev && (tmp->prev->content != '1' && tmp->prev->content != ' '))
				|| (tmp->next && (tmp->next->content != '1' && tmp->next->content != ' '))
				|| (content_up(tmp) != '1' && content_up(tmp) != ' ')
				|| (content_down(data, tmp) != '1' && content_down(data, tmp) != ' '))
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

t_map	*new_map(t_data *data)
{
	t_map	*new;
	int		i;

	new = NULL;
	i = 0;
	while (i != data->size.xmax + 3)
	{
		if (i == data->size.xmax + 2)
			add_map(&new, ' ', 0, 1);
		else
			add_map(&new, ' ', i, 0);
		i++;
	}
	return (new_map2(data, new));
}

t_map	*new_map2(t_data *data, t_map *new)
{
	t_map	*tmp;
	int		i;

	tmp = data->map;
	i = 1;
	while (tmp)
	{
		add_map(&new, tmp->content, tmp->x + 1, tmp->y + 1);
		if (tmp->x == (data->size.xmax - 1))
		{
			add_map(&new, ' ', data->size.xmax + 1, i);
			add_map(&new, ' ', 0, i + 1);
			i++;
		}
		tmp = tmp->next;
	}
	i = 0;
	while (i != data->size.xmax + 1)
	{
		add_map(&new, ' ', i + 1, data->size.ymax + 1);
		i++;
	}
	return (new);
}
