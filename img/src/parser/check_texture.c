/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:18:33 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/11 14:46:37 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

int	check_texture(t_data *data)
{
	int	status;
	int	i;
	
	status = 0;
	i = 0;
	while (i == status && i != 6)
	{
		if (!data->parse.texture_path[i])
			ft_putstr_fd("Error\nMissing texture\n", 2);
		else if (i <= 3 && open(data->parse.texture_path[i], O_RDONLY) == -1)
			ft_putstr_fd("Error\nBad texture\n", 2);
		else if (i > 3 && !check_color(data->parse.texture_path[i]))
			ft_putstr_fd("Error\nBad color\n", 2);
		else
			status++;
		i++;
	}
	if (i != status)
		return (0);
	return (1);
}

int	check_color(char *str)
{
	char	**arg;
	int		i;
	
	if (check_coma(str) != 2)
		return (0);
	arg = ft_split(str, ',');
	i = 0;
	while (arg[i])
	{
		if (ft_atoi_color(arg[i]) > 255 || ft_atoi_color(arg[i]) < 0)
			break;
		i++;
	}
	free_tab(arg);
	if (i != 3)
		return (0);
	return (1);
}

int	check_coma(char *str)
{
	int	coma;
	int	i;

	coma = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			coma++;
		i++;
	}
	return (coma);
}