

#include "../include/header.h"

int main (int ac, char **av)
{
    t_data  *data;

    if (ac != 2)
    {
        printf("Error\nUsage: ./cub3D <map.cub>\n");
        return (1);
    }
    
    // Initialize data structure
    data = init_data();
    if (!data)
    {
        printf("Error\nFailed to initialize data\n");
        return (1);
    }
    
    if (!parse_file(av[1], data))
    {
        free_data(data);
        return (1);
    }
    
    // Load textures into mlx images
    if (!load_textures(data))
    {
        free_data(data);
        return (1);
    }
        
    // Debug: Print parsed data
    printf("✓ Parsing successful!\n");
    printf("North texture: %s (%dx%d)\n", data->textures.north,
        data->textures.north_img.width, data->textures.north_img.height);
    printf("South texture: %s (%dx%d)\n", data->textures.south,
        data->textures.south_img.width, data->textures.south_img.height);
    printf("East texture: %s (%dx%d)\n", data->textures.east,
        data->textures.east_img.width, data->textures.east_img.height);
    printf("West texture: %s (%dx%d)\n", data->textures.west,
        data->textures.west_img.width, data->textures.west_img.height);
    printf("Floor color: %d\n", data->colors.floor);
    printf("Ceiling color: %d\n", data->colors.ceiling);
    printf("Player position: (%.2f, %.2f)\n", data->player.pos_x,
        data->player.pos_y);
    printf("Player direction: %c\n", data->player.direction);
    printf("Map dimensions: %dx%d\n", data->map.width, data->map.height);
    
    // TODO: Initialize game and start raycasting
    
    // Clean up
    free_data(data);
    return (0);
}