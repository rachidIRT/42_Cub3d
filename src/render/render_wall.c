/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roubelka <roubelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:03:21 by roubelka          #+#    #+#             */
/*   Updated: 2026/03/05 17:03:22 by roubelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

t_img	*get_wall_texture(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ang_cos < 0)
			return (&data->textures.east_img);
		return (&data->textures.west_img);
	}
	if (ray->ang_sin < 0)
		return (&data->textures.south_img);
	return (&data->textures.north_img);
}

void	calc_wall_projection(t_ray *ray, t_render *r, double ang)
{
	double	fov;

	r->wall_dist = ray->len * cos(ray->angle - ang);
	if (r->wall_dist < 0.01)
		r->wall_dist = 0.01;
	fov = (FOV_DEG * M_PI) / 180.0;
	r->proj_dist = (SCREEN_WIDTH / 2.0) / tan(fov / 2.0);
	r->line_height = (int)(r->proj_dist / r->wall_dist);
	r->draw_start = -r->line_height / 2 + SCREEN_HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + SCREEN_HEIGHT / 2;
	if (r->draw_end >= SCREEN_HEIGHT)
		r->draw_end = SCREEN_HEIGHT - 1;
}

static void	fix_tex_x(t_ray *ray, t_render *r, int tex_w)
{
	if (ray->side == 0 && ray->ang_cos < 0)
		r->tex_x = tex_w - r->tex_x - 1;
	if (ray->side == 1 && ray->ang_sin > 0)
		r->tex_x = tex_w - r->tex_x - 1;
	if (r->tex_x < 0)
		r->tex_x = 0;
	if (r->tex_x >= tex_w)
		r->tex_x = tex_w - 1;
}

void	calc_texture_coords(t_data *data, t_ray *ray, t_render *r)
{
	t_img	*tex;

	if (ray->side == 0)
		r->wall_x = data->player.pos_y + ray->len * ray->ang_sin;
	else
		r->wall_x = data->player.pos_x + ray->len * ray->ang_cos;
	r->wall_x -= floor(r->wall_x);
	tex = get_wall_texture(data, ray);
	r->tex_x = (int)(r->wall_x * tex->width);
	fix_tex_x(ray, r, tex->width);
}

void	draw_wall_column(t_data *data, t_ray *ray, t_render *r, int x)
{
	t_img			*tex;
	int				y;
	int				d;
	unsigned int	color;

	tex = get_wall_texture(data, ray);
	if (r->line_height <= 0)
		return ;
	y = r->draw_start;
	while (y <= r->draw_end)
	{
		d = y * 256 - SCREEN_HEIGHT * 128 + r->line_height * 128;
		r->tex_y = ((d * tex->height) / r->line_height) / 256;
		if (r->tex_y < 0)
			r->tex_y = 0;
		if (r->tex_y >= tex->height)
			r->tex_y = tex->height - 1;
		color = get_tex_pixel(tex, r->tex_x, r->tex_y);
		put_pixel(&data->frame, x, y, color);
		y++;
	}
}
