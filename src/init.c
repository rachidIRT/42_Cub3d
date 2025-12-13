/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roubelka <roubelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:34:38 by roubelka          #+#    #+#             */
/*   Updated: 2025/12/08 23:26:08 by roubelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

t_data  *init_data(void)
{
    t_data  *data;

    data = malloc(sizeof(t_data));
    if (!data)
        return (NULL);
    
    // Initialize textures
    data->textures.north = NULL;
    data->textures.south = NULL;
    data->textures.east = NULL;
    data->textures.west = NULL;
    // Initialize colors
    data->colors.floor = -1;
    data->colors.ceiling = -1;
    // Initialize player
    data->player.pos_x = -1;
    data->player.pos_y = -1;
    data->player.direction = '\0';
    // Initialize map
    data->map.grid = NULL;
    data->map.width = 0;
    data->map.height = 0;
    data->map_lines = NULL;
    // Initialize flags
    data->parsed_no = false;
    data->parsed_so = false;
    data->parsed_we = false;
    data->parsed_ea = false;
    data->parsed_f = false;
    data->parsed_c = false;
    data->map_started = false;
    
    return (data);
}

// void    free_textures(t_data *data)
// {
//     if (data->textures.north)
//         free(data->textures.north);
//     if (data->textures.south)
//         free(data->textures.south);
//     if (data->textures.east)
//         free(data->textures.east);
//     if (data->textures.west)
//         free(data->textures.west);
// }

void    free_map(t_data *data)
{
    int i;

    if (!data->map.grid)
        return;
    
    i = 0;
    while (i < data->map.height)
    {
        if (data->map.grid[i])
            free(data->map.grid[i]);
        i++;
    }
    free(data->map.grid);
}

void    free_map_lines(t_map_line *head)
{
    t_map_line  *tmp;

    while (head)
    {
        tmp = head->next;
        if (head->line)
            free(head->line);
        free(head);
        head = tmp;
    }
}

void    free_data(t_data *data)
{
    if (!data)
        return;
    free_map(data);
    // pause();   
    // free_textures(data);
    
    free_map_lines(data->map_lines);
    free(data);
}