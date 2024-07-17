/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:35:51 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/17 18:21:32 by mgayout          ###   ########.fr       */
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

# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05
# define WIDTH 1500
# define HEIGHT 1000

typedef struct s_key
{
	int		up;
	int		right;
	int		down;
	int		left;
	int		cam_left;
	int		cam_right;
	int		minimap;
	int		minimap_updated;
	int		door;
	int		door_updated;
}				t_key;

typedef struct s_image
{
	void			*mlx_img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				tex_width;
	int				tex_height;
}					t_image;

typedef struct s_tmp
{
	t_image				select_tex;
	int					tex_num;
	double				wall_x;
	int					tex_x;
	int					tex_y;
}						t_tmp;

typedef struct s_draw
{
	struct s_tmp		wall;
	int					line_height;
	int					draw_start;
	int					draw_end;
	int					**buffer;
	struct s_image		img;
}						t_draw;

typedef struct s_ray
{
	double				camera;
	double				ray_dirx;
	double				ray_diry;
	double				delta_distx;
	double				delta_disty;
	double				side_distx;
	double				side_disty;
	int					stepx;
	int					stepy;
	int					mapx;
	int					mapy;
	int					hit_side;
	double				perp_wall_dist;
	int					door;
}						t_ray;

typedef struct s_mini
{
	struct s_image		background;
	struct s_image		wall;
	struct s_image		door;
	struct s_image		player;
}						t_mini;

typedef struct s_texture
{
	struct s_mini	minimap;
	struct s_image	door;
	struct s_image	nwall;
	struct s_image	ewall;
	struct s_image	swall;
	struct s_image	wwall;
	int				c_wall;
	int				f_wall;
}					t_texture;

typedef struct s_player
{
	char			dir;
	int				x;
	int				y;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
}					t_player;

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
	int				xmax;
	int				ymax;
}						t_parse;

typedef struct s_data
{
	void				*mlx;
	void				*mlx_win;
	struct s_parse		parse;
	struct s_player		player;
	struct s_texture	texture;
	struct s_ray		ray;
	struct s_draw		draw;
	struct s_key		key;
}						t_data;

//MAIN
int		print_error(char *str);
void	init_game(t_data *data);
int		update(t_data *data);

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
void	fill_map(t_map **map);
void	add_map_space(t_map *map, char c, int x, int y);

//MAP_UTILS
t_map	*last_map(t_map **map);
int		find_xmax(t_map **map);
int		find_ymax(t_map **map);
void	print_map(t_map *map);

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
int		check_closest_block(t_map *map, int x, int y, char c);
char	content_up(t_map *map);
char	content_down(t_map *map);
int		ft_atoi_color(char *str);

//INIT
void	init_data(t_data *data);
void	init_player(t_data *data, t_player *player);
void	init_ns_dir(t_player *player);
void	init_ew_dir(t_player *player);
void	init_ray(t_ray *ray);

//TEXTURE
void	init_texture(t_data *data);
void	wall_texture(t_data *data);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
int		create_rgb(int r, int g, int b);

//DRAW
void	draw(t_data *data);
void	init_buffer(t_data *data);
void	draw_cf(t_data *data);
void	draw_wall(t_data *data);
void	init_img(t_data *data);

//KEY
void	key_signal(t_data *data);
int		press_key(int key, t_data *data);
int		release_key(int key, t_data *data);

//CALCUL
void	calculate_delta(t_data *data);
void	calculate_side_dist(t_data *data);
void	exec_dda(t_data *data, int x);
void	calc_perp_wall_dist(t_data *data);
void	calc_height_wall(t_data *data);

//RAYCASTING
void	raycasting(t_data *data);
void	init_tex_dir(t_data *data);
void	calc_wall_x(t_data *data);
void	calc_x_coord_tex(t_data *data);
void	color_x_stripe(t_data *data, int x);

//MINIMAP
void	draw_minimap(t_data *data);
t_map	*find_minimap_pos(t_data *data, int x, int y);
t_map	*find_prev_pos(t_data *data, int x, int y);
t_map	*find_next_pos(t_data *data, int x, int y);
int		draw_minimap_wall(t_data *data, int x, int y);
int		draw_minimap_door(t_data *data, int x, int y);
int		draw_minimap_player(t_data *data, int x, int y);

//MOVE
void	move(t_data *data);
void	move_playerx(t_data *data, int n);
void	move_playery(t_data *data, int n);
void	move_cam(t_data *data, int n);

//UTILS
t_map	*find_block(t_map *map, int x, int y);
t_map	*find_player(t_data *data);

//FREE
int		free_all(t_data *data);
void	free_texture(char **texture_path);
void	free_map(t_map **map);
void	free_buffer(t_data *data);
void	free_tab(char **str);

#endif