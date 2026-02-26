#include "../../include/header.h"

static void	set_key(t_data *data, int keycode, char val)
{
	if (keycode == 119 || keycode == 115
		|| keycode == 97 || keycode == 100)
		data->keys[keycode % 512] = val;
	if (keycode == 65361 || keycode == 65363)
		data->keys[keycode % 512] = val;
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
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
