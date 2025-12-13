/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roubelka <roubelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 21:57:54 by roubelka          #+#    #+#             */
/*   Updated: 2025/12/09 00:17:56 by roubelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

int is_surrounded_by_walls(t_data *data, int y, int x)
{
    // Check if on edge
    if (y == 0 || y == data->map.height - 1)
        return (0);
    if (x == 0 || x == data->map.width - 1)
        return (0);
    
    // Check all 4 directions for spaces
    if (data->map.grid[y - 1][x] == ' ')
        return (0);
    if (data->map.grid[y + 1][x] == ' ')
        return (0);
    if (data->map.grid[y][x - 1] == ' ')
        return (0);
    if (data->map.grid[y][x + 1] == ' ')
        return (0);
    
    return (1);
}

int find_player(t_data *data)
{
    int player_count;
    int i;
    int j;
    char c;

    player_count = 0;
    i = 0;
    while (i < data->map.height)
    {
        j = 0;
        while (j < data->map.width)
        {
            c = data->map.grid[i][j];
            if (is_player_char(c))
            {
                player_count++;
                data->player.pos_x = j + 0.5;
                data->player.pos_y = i + 0.5;
                data->player.direction = c;
            }
            j++;
        }
        i++;
    }
    
    if (player_count == 0)
        printf("No player found in map");
    if (player_count > 1)
        printf("Multiple players found in map");
    
    return (1);
}

int validate_map(t_data *data)
{
    int i;
    int j;
    char c;

    // Check all characters are valid
    i = 0;
    while (i < data->map.height)
    {
        j = 0;
        while (j < data->map.width)
        {
            c = data->map.grid[i][j];
            if (!is_valid_map_char(c))
                printf("Invalid character in map");
            
            // Check if walkable spaces are surrounded by walls
            if (is_walkable(c))
            {
                if (!is_surrounded_by_walls(data, i, j))
                    printf("Map is not closed by walls");
            }
            j++;
        }
        i++;
    }
    
    // Find and validate player
    if (!find_player(data))
        return (0);
    
    return (1);
}

int validate_data(t_data *data)
{
    // check all texture are present
    if (!data->textures.north || !data->textures.east ||
        !data->textures.south || !data->textures.west)
        printf("Missing texture(s)");
    // Check colors are present
    if (data->colors.ceiling == -1)
        printf("Missing ceiling color");
    if (data->colors.floor == -1)
        printf("Missing floor color");
    // Check map exists
    if (!data->map.grid)
        printf("Missing map");
    // Validate map structure
    if (!validate_map(data))
        return (0);
    
    return (1);
}