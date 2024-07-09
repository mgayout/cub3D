/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:16:55 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/09 15:13:11 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	init_wall(t_data *data, char *file)
{
	char	*line;
	int		status;
	int		i;
	int		j;

	status = 0;
	i = 0;
	while (file[i] && status != 6)
	{
		j = i;
		while (file[i] != '\n')
			i++;
		if (i != j)
			line = ft_substr(file, j, i - j);
		else
			line = NULL;
		status = init_wall2(data, line, status);
		if (line)
			free(line);
		i++;
	}
	if (status != 6)
		return (-1);
	return (i);	
}

int	init_wall2(t_data *data, char *line, int status)
{
	if (line && check_line(line) && check_arg(line))
		status += add_texture(data, line);
	else if (line && check_line(line) && !check_arg(line))
	{
		printf("line = %s\n", line);
		free_texture(&data->texture);
		free(data->file);
		free(line);
		print_error("Error\nBad texture\n", 1);
	}
	return (status);
}

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\n')
		return (0);
	return (1);
}

int	check_arg(char *line)
{
	char	**arg;

	arg = ft_split(line, ' ');
	if (!arg[0] || !arg[1] || arg[2])
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
	if (!ft_strncmp(arg[0], "NO", 3) && !data->texture.nwall_path)
		data->texture.nwall_path = ft_strdup(arg[1]);
	else if (!ft_strncmp(arg[0], "EA", 3) && !data->texture.ewall_path)
		data->texture.ewall_path = ft_strdup(arg[1]);
	else if (!ft_strncmp(arg[0], "SO", 3) && !data->texture.swall_path)
		data->texture.swall_path = ft_strdup(arg[1]);
	else if (!ft_strncmp(arg[0], "WE", 3) && !data->texture.wwall_path)
		data->texture.wwall_path = ft_strdup(arg[1]);
	else if (!ft_strncmp(arg[0], "C", 2) && !data->texture.cwall_color)
		data->texture.cwall_color = ft_strdup(arg[1]);
	else if (!ft_strncmp(arg[0], "F", 2) && !data->texture.fwall_color)
		data->texture.fwall_color = ft_strdup(arg[1]);
	free_tab(arg);
	return (1);
}
