/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:18:33 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/22 14:57:25 by mgayout          ###   ########.fr       */
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
		else if (i <= 3 && (open(data->parse.texture_path[i], O_RDONLY) == -1
				|| open(data->parse.texture_path[i], __O_DIRECTORY) != -1
				|| !is_a_xpm(data->parse.texture_path[i])))
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

int	is_a_xpm(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i < 4 || str[i - 4] != '.' || str[i - 3] != 'x'
		|| str[i - 2] != 'p' || str[i - 1] != 'm')
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
			break ;
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

int	ft_atoi_color(char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i++] - '0');
	}
	if (str[i] != '\0' && str[i] != '\n')
		return (256);
	return (result * sign);
}
