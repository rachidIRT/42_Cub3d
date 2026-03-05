/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-most <ael-most@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:14:43 by ael-most          #+#    #+#             */
/*   Updated: 2026/03/05 22:14:44 by ael-most         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static int	check_wall(t_data *data, double x, double y)
{
	double	m;

	m = 0.2;
	if ((int)(x + m) < 0 || (int)(x + m) >= data->map.width
		|| (int)(y + m) < 0 || (int)(y + m) >= data->map.height
		|| data->map.grid[(int)(y + m)][(int)(x + m)] == '1')
		return (1);
	if ((int)(x - m) < 0 || (int)(x - m) >= data->map.width
		|| data->map.grid[(int)(y + m)][(int)(x - m)] == '1')
		return (1);
	if ((int)(y - m) < 0 || (int)(y - m) >= data->map.height
		|| data->map.grid[(int)(y - m)][(int)(x + m)] == '1')
		return (1);
	if (data->map.grid[(int)(y - m)][(int)(x - m)] == '1')
		return (1);
	return (0);
}

void	move_forward(t_data *data)
{
	double	nx;
	double	ny;

	nx = data->player.pos_x + cos(data->player.ang) * MOVE_SPEED;
	ny = data->player.pos_y + sin(data->player.ang) * MOVE_SPEED;
	if (!check_wall(data, nx, data->player.pos_y))
		data->player.pos_x = nx;
	if (!check_wall(data, data->player.pos_x, ny))
		data->player.pos_y = ny;
}

void	move_backward(t_data *data)
{
	double	nx;
	double	ny;

	nx = data->player.pos_x - cos(data->player.ang) * MOVE_SPEED;
	ny = data->player.pos_y - sin(data->player.ang) * MOVE_SPEED;
	if (!check_wall(data, nx, data->player.pos_y))
		data->player.pos_x = nx;
	if (!check_wall(data, data->player.pos_x, ny))
		data->player.pos_y = ny;
}

void	strafe_left(t_data *data)
{
	double	nx;
	double	ny;
	double	a;

	a = data->player.ang - M_PI / 2;
	nx = data->player.pos_x + cos(a) * MOVE_SPEED;
	ny = data->player.pos_y + sin(a) * MOVE_SPEED;
	if (!check_wall(data, nx, data->player.pos_y))
		data->player.pos_x = nx;
	if (!check_wall(data, data->player.pos_x, ny))
		data->player.pos_y = ny;
}

void	strafe_right(t_data *data)
{
	double	nx;
	double	ny;
	double	a;

	a = data->player.ang + M_PI / 2;
	nx = data->player.pos_x + cos(a) * MOVE_SPEED;
	ny = data->player.pos_y + sin(a) * MOVE_SPEED;
	if (!check_wall(data, nx, data->player.pos_y))
		data->player.pos_x = nx;
	if (!check_wall(data, data->player.pos_x, ny))
		data->player.pos_y = ny;
}
