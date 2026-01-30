

#include "../../include/header.h"

static int check_comma_count(char *str)
{
    int count;
    int i;

    count = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == ',')
            count++;
        i++;
    }
    if (count != 2)
    {
        printf("Error\nInvalid color format (must have exactly 2 commas)\n");
        return (0);
    }
    return (1);
}

static int check_valid_chars(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]) && str[i] != ',' && !ft_isspace(str[i]))
        {
            printf("Error\nInvalid character in color string\n");
            return (0);
        }
        i++;
    }
    return (1);
}

int rgb_to_int(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b);
}

static int  validate_rgb(int r, int g, int b)
{
    if (r < 0 || r > 255)
    {
        printf("Error\nRed value must be 0-255\n");
        return (0);
    }
    if (g < 0 || g > 255)
    {
        printf("Error\nGreen value must be 0-255\n");
        return (0);
    }
    if (b < 0 || b > 255)
    {
        printf("Error\nBlue value must be 0-255\n");
        return (0);
    }
    return (1);
}

int parse_rgb(char *str, int *r, int *g, int *b)
{
    char    **split;

    split = ft_split(str, ',');
    if (!split)
    {
        printf("Error\nFailed to parse RGB values\n");
        return (0);
    }
    
    // Check we have exactly 3 components
    if (!split[0] || !split[1] || !split[2] || split[3])
    {
        free_split(split);
        printf("Error\nInvalid RGB format (need R,G,B)\n");
        return (0);
    }
    
    // Parse values
    *r = ft_atoi(split[0]);
    *g = ft_atoi(split[1]);
    *b = ft_atoi(split[2]);
    
    free_split(split);
    
    // Validate range
    if (!validate_rgb(*r, *g, *b))
        return (0);
    
    return (1);
}

int parse_color(char *line, t_data *data, char type)
{
    int     r;
    int     g;
    int     b;
    char    *color_str;

    // Check for duplicates
    if (type == 'F' && data->parsed_f)
    {
        printf("Error\nDuplicate floor color\n");
        return (0);
    }
    if (type == 'C' && data->parsed_c)
    {
        printf("Error\nDuplicate ceiling color\n");
        return (0);
    }
    
    // Skip identifier (1 char) and spaces
    color_str = skip_spaces(line + 1);
    if (!*color_str)
    {
        printf("Error\nMissing color values\n");
        return (0);
    }
    
    if (!check_comma_count(color_str) || !check_valid_chars(color_str))
        return (0);
    
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