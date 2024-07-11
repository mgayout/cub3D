/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 08:03:07 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/11 15:31:40 by mgayout          ###   ########.fr       */
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
# include <stdbool.h>

# include "../libft/libft.h"
# include "../libft/ft_printf+/ft_printf.h"
# include "../libft/get_next_line+/get_next_line.h"

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

typedef struct s_size
{
	int				screen_width;
	int				screen_height;
	int				xmax;
	int				ymax;
	int				block;
	int				wall;
	int				player;
	int				moovex;
	int				moovey;
}					t_size;

typedef struct s_tex
{
	void			*mlx_img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				tex_width;
	int				tex_height;
}					t_tex;

typedef struct s_texture
{
	struct s_tex	wall;
	struct s_tex	player;
	struct s_tex	air_player;
	
	struct s_tex	nwall;
	struct s_tex	ewall;
	struct s_tex	swall;
	struct s_tex	wwall;
	int				c_wall;
	int				f_wall;
}					t_texture;

typedef struct s_map
{
	char			content;
	int				x;
	int				y;
	struct s_map	*prev;
	struct s_map	*next;
}					t_map;

typedef struct s_parse
{
	char			*file;
	struct s_map	*map;
	char			**texture_path;
}						t_parse;

typedef struct s_data
{
	void				*mlx;
	void				*mlx_win;
	int					**buffer;
	struct s_tex		img;
	struct s_size		size;
	struct s_texture	texture;
	struct s_parse		parse;
	int					*ray;
}						t_data;

//MAIN
int		print_error(char *str);
void	init_buffer(t_data *data);
void	init_game(t_data *data);

//PARSER
void	init_file(t_data *data, char *file);
void	init_arg(t_data *data);

//WALL
int		init_wall(t_data *data, char *file, int status);
int		check_line(char *line);
int		check_arg(char *line);
int		add_texture(t_data *data, char *line);

//MAP
int		init_map(t_data *data, char *file, int start);
void	add_map(t_map **map, char content, int x, int y);

//MAP_UTILS
t_map	*last_map(t_map **map);
void	print_map(t_map *map);

//SIZE
void	init_size(t_data *data);
void	xy_max(t_data *data);
void	block_size(t_data *data);

//CHECK_TEXTURE
int		check_texture(t_data *data);
int		check_color(char *str);
int		check_coma(char *str);

//CHECK_MAP
int		check_map(t_data *data);
int		valid_char(t_data *data);
int		valid_player(t_data *data);
int		closed_map(t_data *data);
t_map	*new_map(t_data *data);
t_map	*new_map2(t_data *data, t_map *new);

//PARSER_UTILS
char	content_up(t_map *map);
char	content_down(t_data *data, t_map *map);
int		ft_atoi_color(char *str);
void	fill_map(t_data *data, t_map **map);
void	add_map_space(t_map *map, char c, int x, int y);

//TEXTURE
void	create_texture(t_data *data);
void	render_background(t_data *data, t_tex *img, int color);
void	img_pix_put(t_tex *img, int x, int y, int color);

//DRAW
int		draw(t_data *data);
int		update_player(t_data *data, int x, int y);

//KEY
int		press_key(int key, t_data *data);
int		walled(t_data *data, int x, int y);

//UTILS
t_map	*find_block(t_data *data, int x, int y);
t_map	*find_block_pixel(t_data *data, int x, int y);
t_map	*find_player(t_data *data);

//FREE
int		free_all(t_data *data);
void	free_texture(char **texture_path);
void	free_map(t_map **map);
void	free_buffer(t_data *data);
void	free_tab(char **str);

//int	*init_ray(void);
void	update_changes(t_data *data);
void	put_cf_in_buffer(t_data *data);
void	init_img(t_data *data);
void	my_mlx_pixel_put(t_data *data, t_tex *img, int x, int y, int color);
int		create_rgb(int r, int g, int b);

#endif