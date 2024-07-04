/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:16:55 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/04 19:34:27 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	init_walls(t_data *data, char *file)
{
	char	**split_arg;
	int		status;
	int		i;

	split_arg = ft_split(file, '\n');
	status = 0;
	i = 0;
	while (split_arg[i] && status != 6)
	{
		if (check_line(split_arg[i]) && check_arg(split_arg[i]))
			status += add_texture(data, split_arg[i]);
		else if (check_line(split_arg[i]) && !check_arg(split_arg[i]))
		{
			free_texture(&data->texture);
			free_tab(split_arg);
			free(data->file);
			print_error("Error\nBad texture\n", 1);
		}
		i++;
	}
	free_tab(split_arg);
	if (status != 6)
		return (-1);
	return (i);	
}

int	check_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

int	check_arg(char *str)
{
	char	**split_arg;

	split_arg = ft_split(str, ' ');
	if (!split_arg[0] || !split_arg[1] || split_arg[2])
	{
		free_tab(split_arg);
		return (0);
	}
	if (ft_strncmp(split_arg[0], "NO", 3) && ft_strncmp(split_arg[0], "EA", 3)
			&& ft_strncmp(split_arg[0], "SO", 3) && ft_strncmp(split_arg[0], "WE", 3)
			&& ft_strncmp(split_arg[0], "F", 2) && ft_strncmp(split_arg[0], "C", 2))
	{
		free_tab(split_arg);
		return (0);
	}
	free_tab(split_arg);
	return (1);
}

int	add_texture(t_data *data, char *arg)
{
	char	**split_arg;

	split_arg = ft_split(arg, ' ');
	if (!ft_strncmp(split_arg[0], "NO", 3) && !data->texture.nwall_path)
		data->texture.nwall_path = ft_strdup(split_arg[1]);
	else if (!ft_strncmp(split_arg[0], "EA", 3) && !data->texture.ewall_path)
		data->texture.ewall_path = ft_strdup(split_arg[1]);
	else if (!ft_strncmp(split_arg[0], "SO", 3) && !data->texture.swall_path)
		data->texture.swall_path = ft_strdup(split_arg[1]);
	else if (!ft_strncmp(split_arg[0], "WE", 3) && !data->texture.wwall_path)
		data->texture.wwall_path = ft_strdup(split_arg[1]);
	else if (!ft_strncmp(split_arg[0], "C", 2) && !data->texture.cwall_color)
		data->texture.cwall_color = ft_strdup(split_arg[1]);
	else if (!ft_strncmp(split_arg[0], "F", 2) && !data->texture.fwall_color)
		data->texture.fwall_color = ft_strdup(split_arg[1]);
	free_tab(split_arg);
	return (1);
}
