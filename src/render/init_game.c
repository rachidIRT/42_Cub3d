/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roubelka <roubelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:03:08 by roubelka          #+#    #+#             */
/*   Updated: 2026/03/05 17:03:09 by roubelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

void	init_player_angle(t_data *data)
{
	if (data->player.direction == 'N')
		data->player.ang = 3 * M_PI / 2;
	else if (data->player.direction == 'S')
		data->player.ang = M_PI / 2;
	else if (data->player.direction == 'E')
		data->player.ang = 0;
	else if (data->player.direction == 'W')
		data->player.ang = M_PI;
}

int	init_window(t_data *data)
{
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT, "cub3D");
	if (!data->win)
		return (0);
	data->frame.img = mlx_new_image(data->mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->frame.img)
		return (0);
	data->frame.addr = mlx_get_data_addr(data->frame.img,
			&data->frame.bpp, &data->frame.line_len, &data->frame.endian);
	if (!data->frame.addr)
		return (0);
	data->frame.width = SCREEN_WIDTH;
	data->frame.height = SCREEN_HEIGHT;
	return (1);
}
