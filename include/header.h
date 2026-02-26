/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roubelka <roubelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:25:06 by roubelka          #+#    #+#             */
/*   Updated: 2025/12/17 15:25:07 by roubelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include "../mlx/linux/mlx.h"
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

# define SCREEN_WIDTH	1280
# define SCREEN_HEIGHT	720
# define MOVE_SPEED		0.05
# define ROT_SPEED		0.03
# define MOUSE_SENS		0.001
# define FOV_DEG		60
# ifndef M_PI
#  define M_PI			3.14159265358979323846
# endif

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	t_img	north_img;
	t_img	south_img;
	t_img	east_img;
	t_img	west_img;
}	t_textures;

typedef struct s_colors
{
	int	floor;
	int	ceiling;
}	t_colors;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	char	direction;
	double	ang;
	double	mouse_last_x;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_map_line
{
	char				*line;
	struct s_map_line	*next;
}	t_map_line;

typedef struct s_ray
{
	double	angle;
	double	ang_cos;
	double	ang_sin;
	double	delta_x;
	double	delta_y;
	double	side_dist_x;
	double	side_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		hit;
	double	len;
}	t_ray;

typedef struct s_render
{
	double	wall_dist;
	double	proj_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	int		tex_y;
}	t_render;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_textures	textures;
	t_colors	colors;
	t_player	player;
	t_map		map;
	t_map_line	*map_lines;
	t_img		frame;
	bool		parsed_no;
	bool		parsed_so;
	bool		parsed_we;
	bool		parsed_ea;
	bool		parsed_f;
	bool		parsed_c;
	bool		map_started;
	char		keys[512];
}	t_data;

/* init.c */
t_data			*init_data(void);
void			free_data(t_data *data);
void			free_map(t_data *data);
void			free_map_lines(t_map_line *head);

/* parsing/parse_file.c */
int				parse_file(char *filename, t_data *data);
int				parse_line(char *line, t_data *data);

/* parsing/parse_texture.c */
int				parse_texture(char *line, t_data *data, char dir);
int				store_texture(t_data *data, char *path, char dir);

/* parsing/parse_color.c */
int				parse_color(char *line, t_data *data, char type);
int				parse_rgb(char *str, int *r, int *g, int *b);
int				rgb_to_int(int r, int g, int b);

/* parsing/parse_map.c */
int				parse_map_line(char *line, t_data *data);
int				finalize_map(t_data *data);
void			add_map_line(t_data *data, char *line);
int				count_map_lines(t_map_line *head);
int				get_max_width(t_map_line *head);

/* validation/validate.c */
int				validate_data(t_data *data);
int				validate_map(t_data *data);
int				is_surrounded_by_walls(t_data *data, int y, int x);
int				find_player(t_data *data);

/* validation/validate_chars.c */
int				is_valid_map_char(char c);
int				is_player_char(char c);
int				is_walkable(char c);

/* utils/utils.c */
int				check_file_ext(char *filename);
int				check_file_exists(char *path);
void			free_split(char **split);
int				open_file(char *filename);

/* utils/string_utils.c */
int				ft_isspace(char c);
char			*skip_spaces(char *str);
char			*trim_line(char *line);
int				is_empty_line(char *line);

/* textures/load_textures.c */
int				load_textures(t_data *data);
int				load_single_texture(t_data *data, char *path, t_img *img);
void			free_textures(t_data *data);

/* render/init_game.c */
void			init_player_angle(t_data *data);
int				init_window(t_data *data);

/* render/pixel.c */
void			put_pixel(t_img *img, int x, int y, int color);
unsigned int	get_tex_pixel(t_img *img, int x, int y);

/* render/draw.c */
void			draw_floor_ceiling(t_data *data);

/* render/raycasting.c */
void			init_ray_angle(t_data *data, t_ray *ray, int x);
void			init_ray_step(t_data *data, t_ray *ray);
void			perform_dda(t_data *data, t_ray *ray);

/* render/render_wall.c */
t_img			*get_wall_texture(t_data *data, t_ray *ray);
void			calc_wall_projection(t_ray *ray, t_render *r, double ang);
void			calc_texture_coords(t_data *data, t_ray *ray, t_render *r);
void			draw_wall_column(t_data *data, t_ray *ray, t_render *r, int x);

/* render/render.c */
int				render_frame(t_data *data);
void			init_ray(t_data *data, t_ray *ray, int x);
void			cast_single_ray(t_data *data, t_ray *ray, int x);

/* events/events.c */
int				key_press(int keycode, t_data *data);
int				key_release(int keycode, t_data *data);
int				close_game(t_data *data);
int				expose_hook(t_data *data);

/* events/movement.c */
void			move_forward(t_data *data);
void			move_backward(t_data *data);
void			strafe_left(t_data *data);
void			strafe_right(t_data *data);

/* events/game_loop.c */
void			rotate_left(t_data *data);
void			rotate_right(t_data *data);
void			handle_movement(t_data *data);
int				game_loop(t_data *data);

/* events/mouse.c */
void			update_mouse(t_data *data);

#endif
