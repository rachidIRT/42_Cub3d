/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roubelka <roubelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 01:52:45 by roubelka          #+#    #+#             */
/*   Updated: 2025/12/10 00:18:03 by roubelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static int  check_duplicate(t_data *data, char direction)
{
    if (direction == 'N' && data->parsed_no)
    {
        printf("Duplicate NO texture");
        return (0); // yalh zidta mn chatgpt
    }
    if (direction == 'S' && data->parsed_so)
    {
        printf("Duplicate SO texture");
        return (0); // yalh zidta mn chatgpt
    }
    if (direction == 'W' && data->parsed_we)
    {
        printf("Duplicate WE texture");
        return (0); // yalh zidta mn chatgpt
    }
    if (direction == 'E' && data->parsed_ea)
    {
        printf("Duplicate EA texture");
        return (0); // yalh zidta mn chatgpt
    }
    return (1);
}

int store_texture(t_data *data, char *path, char direction)
{
    if (direction == 'N')
    {
        data->textures.north = path;
        data->parsed_no = true;
    }
    else if (direction == 'S')
    {
        data->textures.south = path;
        data->parsed_so = true;
    }
    else if (direction == 'E')
    {
        data->textures.east = path;
        data->parsed_ea = true;
    }
    else if (direction == 'W')
    {
        data->textures.west = path;
        data->parsed_we = true;
    }
    return (1);
}

int parse_texture(char *line, t_data *data, char direction)
{
    char    *path;
    char    *trimmed;
    int     i;

    // Check for duplicates
    if (!check_duplicate(data, direction))
        return (0);
    i = 2;
    while(line[i] && ft_isspace(line[i]))
        i++;
    if (!line[i])
    {
        printf("Missing texture path");
        return (0); // yalh zidta mn chatgpt
    }
    // check ach path shih
    trimmed = trim_line(&line[i]);
    if (!trimmed)
    {
        printf("Memory allocation for texture path failed");
        return (0); // yalh zidta mn chatgpt
    }

    /* DEBUG — show what we try to open */
    // ->// printf("[DBG] parse_texture dir=%c path='%s'\n", direction, trimmed);
    
    if (!check_file_exists(trimmed)) //rah kan flawl (line)
    {
        printf("Texture file not found");
        free(trimmed);
        return (0); // yalh zidta mn chatgpt
    }
    // Duplicate the path for storage
    path = ft_strdup(trimmed);
    free(trimmed);
    if (!path)
    {
        printf("Failed to allocate memory");
        return (0); // yalh zidta mn chatgpt
    }
    // Store in appropriate field
    return (store_texture(data, path, direction));
}
