#include "../../include/header.h"

int	load_single_texture(t_data *data, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(data->mlx, path,
			&img->width, &img->height);
	if (!img->img)
	{
		printf("Error\nFailed to load texture: %s\n", path);
		return (0);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_len, &img->endian);
	if (!img->addr)
	{
		printf("Error\nFailed to get texture data: %s\n", path);
		mlx_destroy_image(data->mlx, img->img);
		img->img = NULL;
		return (0);
	}
	return (1);
}

static void	free_single_texture(t_data *data, t_img *img)
{
	if (img->img && data->mlx)
	{
		mlx_destroy_image(data->mlx, img->img);
		img->img = NULL;
		img->addr = NULL;
	}
}

void	free_textures(t_data *data)
{
	if (!data)
		return ;
	free_single_texture(data, &data->textures.north_img);
	free_single_texture(data, &data->textures.south_img);
	free_single_texture(data, &data->textures.east_img);
	free_single_texture(data, &data->textures.west_img);
	if (data->textures.north)
		free(data->textures.north);
	if (data->textures.south)
		free(data->textures.south);
	if (data->textures.east)
		free(data->textures.east);
	if (data->textures.west)
		free(data->textures.west);
	data->textures.north = NULL;
	data->textures.south = NULL;
	data->textures.east = NULL;
	data->textures.west = NULL;
}

int	load_textures(t_data *data)
{
	if (!load_single_texture(data, data->textures.north,
			&data->textures.north_img))
		return (0);
	if (!load_single_texture(data, data->textures.south,
			&data->textures.south_img))
		return (0);
	if (!load_single_texture(data, data->textures.east,
			&data->textures.east_img))
		return (0);
	if (!load_single_texture(data, data->textures.west,
			&data->textures.west_img))
		return (0);
	return (1);
}
