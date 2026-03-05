/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roubelka <roubelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:02:49 by roubelka          #+#    #+#             */
/*   Updated: 2026/03/05 17:02:50 by roubelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static void	set_key(t_data *data, int keycode, char val)
{
	if (keycode == KEY_W || keycode == KEY_S
		|| keycode == KEY_A || keycode == KEY_D)
		data->keys[keycode] = val;
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		data->keys[keycode] = val;
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_game(data);
	set_key(data, keycode, 1);
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	set_key(data, keycode, 0);
	return (0);
}

int	close_game(t_data *data)
{
	free_data(data);
	exit(0);
	return (0);
}

int	expose_hook(t_data *data)
{
	if (data && data->mlx && data->win && data->frame.img)
		mlx_put_image_to_window(data->mlx, data->win,
			data->frame.img, 0, 0);
	return (0);
}
