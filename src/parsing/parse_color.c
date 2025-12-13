/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roubelka <roubelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 20:06:18 by roubelka          #+#    #+#             */
/*   Updated: 2025/12/10 00:31:19 by roubelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

int rgb_to_int(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b);
}

static int  validate_rgb(int r, int g, int b)
{
    if (r < 0 || r > 255)
        printf("Red value must be 0-255");
    if (g < 0 || g > 255)
        printf("Green value must be 0-255");
    if (b < 0 || b > 255)
        printf("Blue value must be 0-255");
    return (1);
}
static int is_valid_number(char *str)
{
    int i;

    if (!str || !str[0])
        return (0);
    i = 0;
    // Skip leading/trailing spaces (ft_split might leave them)
    while (str[i] && ft_isspace(str[i]))
        i++;
    
    // Must have at least one digit
    if (!str[i] || !(str[i] >= '0' && str[i] <= '9'))
        return (0);
    // Check all chars are digits (until space or end)
    while (str[i] && !ft_isspace(str[i]))
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (0);
        i++;
    }
    // Make sure nothing else after digits (except spaces)
    while (str[i])
    {
        if (!ft_isspace(str[i]))
            return (0);
        i++;
    }
    return (1);
}
int parse_rgb(char *str, int *r, int *g, int *b)
{
    char    **split;
    int     result;
    split = ft_split(str, ',');
    if (!split)
        printf("Failed to parse RGB values");
    // Check we have exactly 3 components
    if (!split[0] || !split[1] || !split[2] || split[3])
    {
        free_split(split);
        printf("Invalid RGB format (need R,G,B)");
    }
    // Validate each component is a valid number
    if (!is_valid_number(split[0]) || !is_valid_number(split[1]) || 
        !is_valid_number(split[2]))
    {
        free_split(split);
        printf("RGB values must be valid numbers (0-255)");
    }
    
    // Parse values
    *r = ft_atoi(split[0]);
    *g = ft_atoi(split[1]);
    *b = ft_atoi(split[2]);
    
    free_split(split);
    
    // Validate range
    result = validate_rgb(*r, *g, *b);
    return (result);
    // if (!validate_rgb(*r, *g, *b))
        // return (0);
    
    // return (1);
}

int parse_color(char *line, t_data *data, char type)
{
    int     r;
    int     g;
    int     b;
    char    *color_str;

    // Check for duplicates
    if (type == 'F' && data->parsed_f)
        printf("Duplicate floor color");
    if (type == 'C' && data->parsed_c)
        printf("Duplicate ceiling color");
    
    // Skip identifier (1 char) and spaces
    color_str = skip_spaces(line + 1);
    if (!*color_str)
        printf("Missing color values");
    
    // Parse RGB
    if (!parse_rgb(color_str, &r, &g, &b))
        return (0);
    
    // Store color
    if (type == 'F')
    {
        data->colors.floor = rgb_to_int(r, g, b);
        data->parsed_f = true;
    }
    else
    {
        data->colors.ceiling = rgb_to_int(r, g, b);
        data->parsed_c = true;
    }
    
    return (1);
}