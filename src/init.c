
#include "../include/header.h"

static void	init_texture_img(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->width = 0;
	img->height = 0;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	// Initialize mlx
	data->mlx = NULL;
	data->win = NULL;
	// Initialize textures paths
	data->textures.north = NULL;
	data->textures.south = NULL;
	data->textures.east = NULL;
	data->textures.west = NULL;
	// Initialize texture images
	init_texture_img(&data->textures.north_img);
	init_texture_img(&data->textures.south_img);
	init_texture_img(&data->textures.east_img);
	init_texture_img(&data->textures.west_img);
	// Initialize colors
	data->colors.floor = -1;
	data->colors.ceiling = -1;
	// Initialize player
	data->player.pos_x = -1;
	data->player.pos_y = -1;
	data->player.direction = '\0';
	// Initialize map
	data->map.grid = NULL;
	data->map.width = 0;
	data->map.height = 0;
	data->map_lines = NULL;
	// Initialize flags
	data->parsed_no = false;
	data->parsed_so = false;
	data->parsed_we = false;
	data->parsed_ea = false;
	data->parsed_f = false;
	data->parsed_c = false;
	data->map_started = false;
	return (data);
}

void	free_map(t_data *data)
{
    int i;

    if (!data->map.grid)
        return;
    
    i = 0;
    while (i < data->map.height)
    {
        if (data->map.grid[i])
            free(data->map.grid[i]);
        i++;
    }
    free(data->map.grid);
}

void    free_map_lines(t_map_line *head)
{
    t_map_line  *tmp;

    while (head)
    {
        tmp = head->next;
        if (head->line)
            free(head->line);
        free(head);
        head = tmp;
    }
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	free_map(data);
	free_textures(data);
	free_map_lines(data->map_lines);
	if (data->win && data->mlx)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		free(data->mlx);
	free(data);
}
