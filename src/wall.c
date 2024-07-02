/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:16:55 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/02 15:39:38 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	init_walls(t_data *data, char *file)
{
	char	*str;
	char	**split_arg;
	int		status;
	int		fd;


	fd = open(file, O_RDONLY);
	str = get_next_line(fd);
	status = 0;
	data->parse_status = 1;
	while (status != 6)
	{
		if (valid_str(str))
		{
			split_arg = ft_split(str, ' ');
			status = add_img(data, split_arg, status);
			free_tab(split_arg);
		}
		if (status == -1)
		{
			close(fd);
			return (1);
		}
		free(str);
		str = get_next_line(fd);
		data->parse_status += 1;
	}
	free(str);
	close(fd);
	return (0);
}

int	add_img(t_data *data, char **arg, int status)
{
	if (!ft_strncmp(arg[0], "NO", 3) && !data->img.n_wall)
		data->img.n_wall = ft_strdup(arg[1]);
	else if (!ft_strncmp(arg[0], "EA", 3) && !data->img.e_wall)
		data->img.e_wall = ft_strdup(arg[1]);
	else if (!ft_strncmp(arg[0], "SO", 3) && !data->img.s_wall)
		data->img.s_wall = ft_strdup(arg[1]);
	else if (!ft_strncmp(arg[0], "WE", 3) && !data->img.w_wall)
		data->img.w_wall = ft_strdup(arg[1]);
	else if (!ft_strncmp(arg[0], "C", 2) && !data->img.c_wall)
		data->img.c_wall = ft_strdup(arg[1]);
	else if (!ft_strncmp(arg[0], "F", 2) && !data->img.f_wall)
		data->img.f_wall = ft_strdup(arg[1]);
	else
		return (-1);
	status += 1;
	return (status);
}

int	valid_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n' && str[i] != '\0')
			return (1);
		i++;
	}
	return (0);	
}