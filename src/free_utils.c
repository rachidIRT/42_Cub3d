/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roubelka <roubelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:56:34 by roubelka          #+#    #+#             */
/*   Updated: 2026/03/05 23:30:51 by roubelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

void	free_map(t_data *data)
{
	int	i;

	if (!data->map.grid)
		return ;
	i = 0;
	while (i < data->map.height)
	{
		if (data->map.grid[i])
			free(data->map.grid[i]);
		i++;
	}
	free(data->map.grid);
	data->map.grid = NULL;
}

void	free_map_lines(t_map_line *head)
{
	t_map_line	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->line)
			free(head->line);
		free(head);
		head = tmp;
	}
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	free_map(data);
	free_textures(data);
	free_map_lines(data->map_lines);
	if (data->frame.img && data->mlx)
		mlx_destroy_image(data->mlx, data->frame.img);
	if (data->win && data->mlx)
		mlx_destroy_window(data->mlx, data->win);
	free(data);
}
