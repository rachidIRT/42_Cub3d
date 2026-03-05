/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roubelka <roubelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:03:17 by roubelka          #+#    #+#             */
/*   Updated: 2026/03/05 17:03:18 by roubelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static void	clamp_cos_sin(t_ray *ray)
{
	if (fabs(ray->ang_cos) < 1e-6)
	{
		if (ray->ang_cos < 0)
			ray->ang_cos = -1e-6;
		else
			ray->ang_cos = 1e-6;
	}
	if (fabs(ray->ang_sin) < 1e-6)
	{
		if (ray->ang_sin < 0)
			ray->ang_sin = -1e-6;
		else
			ray->ang_sin = 1e-6;
	}
}

static void	dda_step(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

void	perform_dda(t_data *data, t_ray *ray)
{
	if (!data->map.grid)
		return ;
	while (!ray->hit)
	{
		dda_step(ray);
		if (ray->map_x < 0 || ray->map_x >= data->map.width
			|| ray->map_y < 0 || ray->map_y >= data->map.height)
			break ;
		if (data->map.grid[ray->map_y]
			&& data->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
	if (!ray->hit)
		return ;
	if (ray->side == 0)
		ray->len = (ray->map_x - data->player.pos_x
				+ (1 - ray->step_x) / 2.0) / ray->ang_cos;
	else
		ray->len = (ray->map_y - data->player.pos_y
				+ (1 - ray->step_y) / 2.0) / ray->ang_sin;
}

void	init_ray_angle(t_data *data, t_ray *ray, int x)
{
	double	fov;
	double	step;

	fov = (FOV_DEG * M_PI) / 180.0;
	step = fov / SCREEN_WIDTH;
	ray->angle = (data->player.ang - fov / 2.0) + (x * step);
	while (ray->angle < 0)
		ray->angle += 2 * M_PI;
	while (ray->angle >= 2 * M_PI)
		ray->angle -= 2 * M_PI;
	ray->ang_cos = cos(ray->angle);
	ray->ang_sin = sin(ray->angle);
	clamp_cos_sin(ray);
}

void	init_ray_step(t_data *data, t_ray *ray)
{
	ray->delta_x = fabs(1.0 / ray->ang_cos);
	ray->delta_y = fabs(1.0 / ray->ang_sin);
	if (ray->ang_cos < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player.pos_x)
			* ray->delta_x;
	}
	if (ray->ang_sin < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player.pos_y)
			* ray->delta_y;
	}
}
