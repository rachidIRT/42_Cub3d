/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roubelka <roubelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:25:06 by roubelka          #+#    #+#             */
/*   Updated: 2025/12/17 15:25:07 by roubelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

static void	setup_hooks(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 17, 0, close_game, data);
	mlx_hook(data->win, 12, 1L << 15, expose_hook, data);
	mlx_loop_hook(data->mlx, game_loop, data);
}

static int	init_game(t_data *data)
{
	init_player_angle(data);
	if (!init_window(data))
	{
		printf("Error\nFailed to initialize window\n");
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
	{
		printf("Error\nUsage: ./cub3D <map.cub>\n");
		return (1);
	}
	data = init_data();
	if (!data)
		return (printf("Error\nFailed to initialize data\n"), 1);
	if (!parse_file(av[1], data))
		return (free_data(data), 1);
	if (!load_textures(data))
		return (free_data(data), 1);
	if (!init_game(data))
		return (free_data(data), 1);
	setup_hooks(data);
	mlx_loop(data->mlx);
	return (0);
}
