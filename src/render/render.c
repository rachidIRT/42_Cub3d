/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roubelka <roubelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:03:25 by roubelka          #+#    #+#             */
/*   Updated: 2026/03/05 17:03:26 by roubelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

void	init_ray(t_data *data, t_ray *ray, int x)
{
	init_ray_angle(data, ray, x);
	ray->map_x = (int)data->player.pos_x;
	ray->map_y = (int)data->player.pos_y;
	ray->hit = 0;
	ray->len = 0;
	ray->side = 0;
	init_ray_step(data, ray);
}

void	cast_single_ray(t_data *data, t_ray *ray, int x)
{
	init_ray(data, ray, x);
	perform_dda(data, ray);
}

static void	render_column(t_data *data, int x)
{
	t_ray		ray;
	t_render	r;

	cast_single_ray(data, &ray, x);
	if (!ray.hit)
		return ;
	calc_wall_projection(&ray, &r, data->player.ang);
	calc_texture_coords(data, &ray, &r);
	draw_wall_column(data, &ray, &r, x);
}

void	render_frame(t_data *data)
{
	int	x;

	draw_floor_ceiling(data);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		render_column(data, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win,
		data->frame.img, 0, 0);
}
