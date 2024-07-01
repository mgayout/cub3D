/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 08:03:07 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/01 12:53:00 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>

# include "../libft/libft.h"
# include "../libft/ft_printf+/ft_printf.h"
# include "../libft/get_next_line+/get_next_line.h"

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

typedef struct s_imgg
{
	void			*voidd;
	char			*voiddd;
}					t_imgg;

typedef struct s_map
{
	char			content;
	int				x;
	int				y;
	struct s_map	*prev;
	struct s_map	*next;
}					t_map;

typedef struct s_data
{
	void				*mlx;
	void				*mlx_win;
	int					height;
	int					width;
	int					pixel_x;
	int					pixel_y;
	struct s_imgg		img;
	struct s_map		*map;
}						t_data;

//MAIN
void	init_game(t_data *data);

//MAP
t_map	*init_map(t_map *map, char *file);
void	fill_map(t_map **map, char content, int x, int y);
t_map	*last_map(t_map **map);
void	print_map(t_map *map);

//IMG
void	init_img(t_data *data);

//DRAW
int		draw(t_data *data);
void	print_square(t_data *data, int x, int y, int color);

//KEY
int		press_key(int key, t_data *data);

//FREE
int	free_all(t_data *data);
void	free_map(t_map **map);

#endif