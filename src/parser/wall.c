/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:16:55 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/22 12:31:46 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

int	init_wall(t_data *data, char *file, int status)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (i >= 0 && file[i] && status != 6)
	{
		line = NULL;
		j = i;
		while (file[i] != '\n')
			i++;
		if (i != j)
		{
			line = ft_substr(file, j, i - j);
			if (line && check_line(line) && check_arg(line))
				status += add_texture(data, line);
			else if (line && check_line(line) && !check_arg(line))
				i = -2;
			free(line);
		}
		i++;
	}
	if (status != 6)
		return (-1);
	return (i);
}

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (0);
	return (1);
}

int	check_arg(char *line)
{
	char	**arg;

	arg = ft_split(line, ' ');
	if (!arg[1] || arg[2])
	{
		free_tab(arg);
		return (0);
	}
	if (ft_strncmp(arg[0], "NO", 3) && ft_strncmp(arg[0], "EA", 3)
		&& ft_strncmp(arg[0], "SO", 3) && ft_strncmp(arg[0], "WE", 3)
		&& ft_strncmp(arg[0], "F", 2) && ft_strncmp(arg[0], "C", 2))
	{
		free_tab(arg);
		return (0);
	}
	free_tab(arg);
	return (1);
}

int	add_texture(t_data *data, char *line)
{
	char	**arg;

	arg = ft_split(line, ' ');
	if (!ft_strncmp(arg[0], "NO", 3) && !data->parse.texture_path[0])
		data->parse.texture_path[0] = ft_strdup(arg[1]);
	else if (!ft_strncmp(arg[0], "EA", 3) && !data->parse.texture_path[1])
		data->parse.texture_path[1] = ft_strdup(arg[1]);
	else if (!ft_strncmp(arg[0], "SO", 3) && !data->parse.texture_path[2])
		data->parse.texture_path[2] = ft_strdup(arg[1]);
	else if (!ft_strncmp(arg[0], "WE", 3) && !data->parse.texture_path[3])
		data->parse.texture_path[3] = ft_strdup(arg[1]);
	else if (!ft_strncmp(arg[0], "C", 2) && !data->parse.texture_path[4])
		data->parse.texture_path[4] = ft_strdup(arg[1]);
	else if (!ft_strncmp(arg[0], "F", 2) && !data->parse.texture_path[5])
		data->parse.texture_path[5] = ft_strdup(arg[1]);
	free_tab(arg);
	return (1);
}
