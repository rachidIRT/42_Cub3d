#include "../../include/header.h"

static int	get_mouse_delta(t_data *data)
{
	int	x;
	int	y;
	int	cx;

	if (!data->mlx || !data->win)
		return (0);
	cx = SCREEN_WIDTH / 2;
	mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
	if (data->player.mouse_last_x < 0)
	{
		mlx_mouse_move(data->mlx, data->win, cx, SCREEN_HEIGHT / 2);
		mlx_mouse_hide(data->mlx, data->win);
		data->player.mouse_last_x = 0;
		return (0);
	}
	if (x == cx)
		return (0);
	mlx_mouse_move(data->mlx, data->win, cx, SCREEN_HEIGHT / 2);
	mlx_mouse_hide(data->mlx, data->win);
	return (x - cx);
}

void	update_mouse(t_data *data)
{
	int		delta;
	double	rot;

	delta = get_mouse_delta(data);
	if (delta == 0)
		return ;
	rot = (double)delta * MOUSE_SENS;
	data->player.ang += rot;
	if (data->player.ang < 0)
		data->player.ang += 2 * M_PI;
	else if (data->player.ang >= 2 * M_PI)
		data->player.ang -= 2 * M_PI;
}
