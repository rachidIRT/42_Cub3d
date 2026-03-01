#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h> 

# define SCREEN_WIDTH	1280
# define SCREEN_HEIGHT	720
# define MOVE_SPEED		0.05
# define ROT_SPEED		0.04
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


# endif