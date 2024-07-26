/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:32:57 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/26 08:57:33 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D_bonus.h"

void	init_file(t_data *data, char *file)
{
	char	*buf;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1 || open(file, __O_DIRECTORY) != -1)
		print_error("Error\nMap's file is invalid\n");
	data->parse.file = NULL;
	buf = get_next_line(fd);
	while (buf)
	{
		if (!data->parse.file)
			data->parse.file = ft_strdup(buf);
		else
			data->parse.file = ft_strjoin_free(data->parse.file, buf, 1);
		free(buf);
		buf = get_next_line(fd);
	}
	close(fd);
}

void	init_arg(t_data *data)
{
	int		start;

	start = 0;
	data->parse.texture_path = malloc(sizeof(char *) * 8);
	while (start != 8)
		data->parse.texture_path[start++] = NULL;
	start = init_wall(data, data->parse.file, 0);
	data->parse.map = NULL;
	if (start > 0 && data->parse.file[start] != '\0')
		init_map(data, data->parse.file, start);
	free(data->parse.file);
	data->parse.xmax = find_xmax(&data->parse.map);
	data->parse.ymax = find_ymax(&data->parse.map);
}
