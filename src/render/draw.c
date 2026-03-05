/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roubelka <roubelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:03:05 by roubelka          #+#    #+#             */
/*   Updated: 2026/03/05 17:03:06 by roubelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static void	draw_half(t_data *data, int start, int end, int color)
{
	int	x;
	int	y;

	y = start;
	while (y < end)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			put_pixel(&data->frame, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_floor_ceiling(t_data *data)
{
	draw_half(data, 0, SCREEN_HEIGHT / 2, data->colors.ceiling);
	draw_half(data, SCREEN_HEIGHT / 2, SCREEN_HEIGHT, data->colors.floor);
}
