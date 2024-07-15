/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:32:57 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/11 13:17:58 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

void	init_file(t_data *data, char *file)
{
	char	*buf;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		print_error("Error\nMap's file is invalid\n");
	data->parse.file = NULL;
	while ((buf = get_next_line(fd)))
	{
		if (!data->parse.file)
			data->parse.file = ft_strdup(buf);
		else
			data->parse.file = ft_strjoin_free(data->parse.file, buf, 1);
		free(buf);
	}
	close(fd);
}

void	init_arg(t_data *data)
{
	int		start;

	start = 0;
	data->parse.texture_path = malloc(sizeof(char *) * 7);
	while (start != 7)
		data->parse.texture_path[start++] = NULL;
	start = init_wall(data, data->parse.file, 0);
	data->parse.map = NULL;
	if (start > 0 && data->parse.file[start] != '\0')
		init_map(data, data->parse.file, start);
	free(data->parse.file);
}
