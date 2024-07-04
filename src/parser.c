/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:19:07 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/04 19:32:52 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	parse_map(t_data *data)
{
	if (valid_char(data))
	{
		printf("Error\nInvalid char\n");
		return (1);
	}
	if (valid_color(data->texture.cwall_color) || valid_color(data->texture.fwall_color))
	{
		printf("Error\nInvalid color\n");
		return (1);
	}
	if (valid_player(data))
	{
		printf("Error\nInvalid player\n");
		return (1);
	}
	if (closed_map(data))
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
		if (!ft_strchr("10 PWENS", tmp->content))
		{
			//printf("content = %c\n", tmp->content);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	valid_color(char *str)
{
	char	**arg;
	int		i;
	
	arg = ft_split(str, ',');
	i = 0;
	while (arg[i])
	{
		if (ft_atoi_color(arg[i]) > 255)
		{
			free_tab(arg);
			return (1);
		}
		i++;
	}
	free_tab(arg);
	return (0);
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
				return (1);
			data->pos.posx = tmp->x;
			data->pos.posy = tmp->y;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	closed_map(t_data *data)
{
	t_map	*new;
	t_map	*tmp;
	int		status;

	new = new_map(data);
	tmp = new;
	status = 0;
	while (tmp)
	{
		if (tmp->content == ' ')
		{
			if ((tmp->prev && (tmp->prev->content != '1' || tmp->prev->content != ' '))
				|| (tmp->next && (tmp->next->content != '1' || tmp->next->content != ' '))
				|| (content_up(tmp) != '1' || content_up(tmp) != ' ')
				|| (content_down(data, tmp) != '1' || content_down(data, tmp) != ' '))
			{
				//printf("x = %d | y = %d\n", tmp->x, tmp->y);
				//if (tmp->prev)
					//printf("prev content = %c\n", tmp->prev->content);
				//if (tmp->next)
					//printf("next content = %c\n", tmp->next->content);
				//printf("up content = %c\n", content_up(tmp));
				//printf("down content = %c\n", content_down(data, tmp));
				status = 1;
				break ;
			}
		}
		tmp = tmp->next;
	}
	free_map(&new);
	//printf("status = %d\n", status);
	return (status);
}

t_map	*new_map(t_data *data)
{
	t_map	*new;
	t_map	*tmp;
	int		i;
	
	new = NULL;
	tmp = data->map;
	i = 0;
	while (i != data->pos.xmax + 3)
	{
		if (i == data->pos.xmax + 2)
			fill_map(&new, ' ', 0, 1);
		else
			fill_map(&new, ' ', i, 0);
		i++;
	}
	i = 1;
	while (tmp)
	{
		fill_map(&new, tmp->content, tmp->x + 1, tmp->y + 1);
		if (tmp->x == (data->pos.xmax - 1))
		{
			fill_map(&new, ' ', data->pos.xmax + 1, i);
			fill_map(&new, ' ', 0, i + 1);
			i++;
		}
		tmp = tmp->next;
	}
	i = 0;
	while (i != data->pos.xmax + 1)
	{
		fill_map(&new, ' ', i + 1, data->pos.ymax + 1);
		i++;
	}
	//print_map(new);
	return (new);
}
