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
	if (data->keys[119 % 512])
		move_forward(data);
	if (data->keys[115 % 512])
		move_backward(data);
	if (data->keys[97 % 512])
		strafe_left(data);
	if (data->keys[100 % 512])
		strafe_right(data);
	if (data->keys[65361 % 512])
		rotate_left(data);
	if (data->keys[65363 % 512])
		rotate_right(data);
}

int	game_loop(t_data *data)
{
	// update_mouse(data);
	handle_movement(data);
	render_frame(data);
	return (0);
}
