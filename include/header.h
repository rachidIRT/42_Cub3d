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
# include <math.h>       // cos(), sin()
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

// STRUCTURES

// Store a single texture image
typedef struct s_img
{
    void    *img;       // mlx image pointer
    char    *addr;      // image data address
    int     width;
    int     height;
    int     bpp;        // bits per pixel
    int     line_len;   // line length
    int     endian;
}   t_img;


// Store texture paths and loaded images
typedef struct s_textures
{
    char    *north;
    char    *south;
    char    *east;
    char    *west;
    t_img   north_img;
    t_img   south_img;
    t_img   east_img;
    t_img   west_img;
}   t_textures;

// Store colors
typedef struct s_colors
{
    int floor;      // RGB as single int
    int ceiling;
}   t_colors;

// Store player 
typedef struct s_player
{
    double  pos_x;      
    double  pos_y;      
    char    direction;  // 'N', 'S', 'E', 'W'
}   t_player;

// Store map 
typedef struct s_map
{
    char    **grid;     // 2D array of the map
    int     width;      
    int     height;     
}   t_map;

// Temporary linked list for map parsing
typedef struct s_map_line
{
    char                *line;
    struct s_map_line   *next;
}   t_map_line;

// Main data structure
typedef struct s_data
{
    void        *mlx;        // mlx connection
    void        *win;        // mlx window (optional, for rendering)
    t_textures  textures;
    t_colors    colors;
    t_player    player;
    t_map       map;
    t_map_line  *map_lines;  // Temporary storage during parsing
    bool        parsed_no;
    bool        parsed_so;
    bool        parsed_we;
    bool        parsed_ea;
    bool        parsed_f;
    bool        parsed_c;
    bool        map_started;
}   t_data;
// ============================================
// FUNCTION PROTOTYPES
// ============================================

// init.c
t_data      *init_data(void);
void        free_data(t_data *data);
// void        free_textures(t_data *data); //*
void        free_map(t_data *data);
void        free_map_lines(t_map_line *head);

// parsing/parse_file.c
int         parse_file(char *filename, t_data *data);
int         parse_line(char *line, t_data *data);

// parsing/parse_texture.c
int         parse_texture(char *line, t_data *data, char direction);
int         store_texture(t_data *data, char *path, char direction);

// parsing/parse_color.c
int         parse_color(char *line, t_data *data, char type);
int         parse_rgb(char *str, int *r, int *g, int *b);
int         rgb_to_int(int r, int g, int b);

// parsing/parse_map.c
int         parse_map_line(char *line, t_data *data);
int         finalize_map(t_data *data);
void        add_map_line(t_data *data, char *line);
int         count_map_lines(t_map_line *head);
int         get_max_width(t_map_line *head);

// validation/validate.c
int         validate_data(t_data *data);
int         validate_map(t_data *data);
int         is_surrounded_by_walls(t_data *data, int y, int x);
int         find_player(t_data *data);

// validation/validate_chars.c
int         is_valid_map_char(char c);
int         is_player_char(char c);
int         is_walkable(char c);

// // utils/error.c
// int         error_msg(char *msg);
// void        error_exit(char *msg, t_data *data);
// int         error_return(char *msg, int ret);

// utils/utils.c
int         check_file_ext(char *filename);
int         check_file_exists(char *path);
void        free_split(char **split);
int         open_file(char *filename);

// utils/string_utils.c
int         ft_isspace(char c);
char        *skip_spaces(char *str);
char        *trim_line(char *line);
int         is_empty_line(char *line);

// textures/load_textures.c
int         load_textures(t_data *data);
int         load_single_texture(t_data *data, char *path, t_img *img);
void        free_textures(t_data *data);

#endif