/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 02:25:08 by rachid            #+#    #+#             */
/*   Updated: 2026/03/05 02:25:09 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

int	init_mlx(t_data *data)
{
	if (!data->mlx)
	{
		data->mlx = mlx_init();
		if (!data->mlx)
		{
			printf("Error\nFailed to initialize mlx\n");
			return (0);
		}
	}
	return (1);
}

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

static void	init_data_textures(t_data *data)
{
	data->textures.north = NULL;
	data->textures.south = NULL;
	data->textures.east = NULL;
	data->textures.west = NULL;
	init_texture_img(&data->textures.north_img);
	init_texture_img(&data->textures.south_img);
	init_texture_img(&data->textures.east_img);
	init_texture_img(&data->textures.west_img);
}

static void	init_data_flags(t_data *data)
{
	data->parsed_no = false;
	data->parsed_so = false;
	data->parsed_we = false;
	data->parsed_ea = false;
	data->parsed_f = false;
	data->parsed_c = false;
	data->map_started = false;
}

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	ft_memset(data, 0, sizeof(t_data));
	data->mlx = NULL;
	data->win = NULL;
	init_data_textures(data);
	data->colors.floor = -1;
	data->colors.ceiling = -1;
	data->player.pos_x = -1;
	data->player.pos_y = -1;
	data->player.direction = '\0';
	data->player.ang = 0.0;
	data->player.mouse_last_x = -1.0;
	data->map.grid = NULL;
	data->map.width = 0;
	data->map.height = 0;
	data->map_lines = NULL;
	init_texture_img(&data->frame);
	init_data_flags(data);
	return (data);
}
