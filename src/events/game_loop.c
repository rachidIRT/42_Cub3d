/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-most <ael-most@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:14:35 by ael-most          #+#    #+#             */
/*   Updated: 2026/03/05 22:14:38 by ael-most         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

void	rotate_left(t_data *data)
{
	data->player.ang -= ROT_SPEED;
	if (data->player.ang < 0)
		data->player.ang += 2 * M_PI;
}

void	rotate_right(t_data *data)
{
	data->player.ang += ROT_SPEED;
	if (data->player.ang >= 2 * M_PI)
		data->player.ang -= 2 * M_PI;
}

void	handle_movement(t_data *data)
{
	if (data->keys[KEY_W])
		move_forward(data);
	if (data->keys[KEY_S])
		move_backward(data);
	if (data->keys[KEY_A])
		strafe_left(data);
	if (data->keys[KEY_D])
		strafe_right(data);
	if (data->keys[KEY_LEFT])
		rotate_left(data);
	if (data->keys[KEY_RIGHT])
		rotate_right(data);
}

int	game_loop(t_data *data)
{
	handle_movement(data);
	render_frame(data);
	return (0);
}
