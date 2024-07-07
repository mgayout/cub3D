/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 08:03:07 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/05 16:27:58 by mgayout          ###   ########.fr       */
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

typedef struct s_pos
{
	int					height;
	int					width;
	int					posx;
	int					posy;
	int					moovex;
	int					moovey;
	int					xmax;
	int					ymax;
}					t_pos;

typedef struct s_tmp
{
	void			*mlx_img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_tmp;

typedef struct s_texture
{
	struct s_tmp		wall;
	struct s_tmp		player;
	struct s_tmp		air;
	char				*nwall_path;
	char				*ewall_path;
	char				*swall_path;
	char				*wwall_path;
	char				*cwall_color;
	char				*fwall_color;
}					t_texture;

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
	char				*file;
	struct s_pos		pos;
	struct s_texture	texture;
	struct s_map		*map;
}						t_data;

//MAIN
int		init_arg(t_data *data, char *file);
void	init_data(t_data *data);
void	init_game(t_data *data);
int		print_error(char *str, int i);

//WALL
int		init_walls(t_data *data, char *file);
int		check_line(char *str);
int		check_arg(char *str);
int		add_texture(t_data *data, char *arg);
char	**ft_split_cub(char const *str, char c);

//MAP
void	init_map(t_data *data, char *file, int start);
void	add_map(t_map **map, char content, int x, int y);
void	fill_map(t_data *data, t_map **map);
void	add_map_space(t_map *map, int x, int y);
t_map	*last_map(t_map **map);
void	print_map(t_map *map);

//PARSER
int		parse_map(t_data *data);
int		valid_char(t_data *data);
int		valid_color(char *str);
int		valid_player(t_data *data);
int		closed_map(t_data *data);
t_map	*new_map(t_data *data);

//PARSER_UTILS
char	content_up(t_map *map);
char	content_down(t_data *data, t_map *map);
int		ft_atoi_color(char *str);

//TEXTURE
void	init_texture(t_data *data);
void	render_background(t_data *data, t_tmp *img, int color);
void	img_pix_put(t_tmp *img, int x, int y, int color);

//DRAW
int		first_draw(t_data *data);
int		draw(t_data *data, int x, int y);

//KEY
int		press_key(int key, t_data *data);
int		walled(t_data *data, int x, int y);
int		*moove_up(t_data *data, int x, int y);
int		*moove_down(t_data *data, int x, int y);

//FREE
int		free_all(t_data *data);
void	free_map(t_map **map);
void	free_texture(t_texture *texture);
void	free_tab(char **str);

#endif