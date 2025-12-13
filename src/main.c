/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roubelka <roubelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:38:23 by roubelka          #+#    #+#             */
/*   Updated: 2025/12/09 23:07:03 by roubelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

int main (int ac, char **av)
{
    t_data  *data;

    if (ac != 2)
        printf("Usage: ./cub3D <map.cub>");
    
    // Initialize data structure
    data = init_data();
    if (!data)
        printf("Failed to initialize data");
    if(!parse_file(av[1], data))
    {
        free_data(data);
        return (1);
    }
        
        // Debug: Print parsed data
    printf("✓ Parsing successful!\n");
    printf("North texture: %s\n", data->textures.north);
    printf("South texture: %s\n", data->textures.south);
    printf("East texture: %s\n", data->textures.east);
    printf("West texture: %s\n", data->textures.west);
    printf("Floor color: %d\n", data->colors.floor);
    printf("Ceiling color: %d\n", data->colors.ceiling);
    printf("Player position: (%.2f, %.2f)\n", data->player.pos_x, data->player.pos_y);
    printf("Player direction: %c\n", data->player.direction);
    printf("Map dimensions: %dx%d\n", data->map.width, data->map.height);
    
    // TODO: Initialize game and start raycasting
    
    // Clean up
    free_data(data);
    return (0);
}