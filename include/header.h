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

#ifndef HEADER_H
# define HEADER_H

# include "cub3d.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

# ifdef __linux__
#  include "../mlx/linux/mlx.h"
# else
#  include "../mlx/macos/mlx.h"
# endif

/* init_utils.c */
t_data			*init_data(void);
int             init_mlx(t_data *data);

/* free_utils.c */
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
void			render_frame(t_data *data);
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
// void			update_mouse(t_data *data);

# endif
