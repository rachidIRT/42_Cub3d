/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roubelka <roubelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:59:43 by roubelka          #+#    #+#             */
/*   Updated: 2026/03/05 16:59:44 by roubelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	parse_rgb(char *str, int *r, int *g, int *b)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split)
	{
		printf("Error\nFailed to parse RGB values\n");
		return (0);
	}
	if (!split[0] || !split[1] || !split[2] || split[3])
	{
		free_split(split);
		printf("Error\nInvalid RGB format (need R,G,B)\n");
		return (0);
	}
	*r = ft_atoi(split[0]);
	*g = ft_atoi(split[1]);
	*b = ft_atoi(split[2]);
	free_split(split);
	if (!validate_rgb(*r, *g, *b))
		return (0);
	return (1);
}

static int	check_color_duplicate(t_data *data, char type)
{
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
	return (1);
}

static void	store_color(t_data *data, char type, int rgb_int)
{
	if (type == 'F')
	{
		data->colors.floor = rgb_int;
		data->parsed_f = true;
	}
	else
	{
		data->colors.ceiling = rgb_int;
		data->parsed_c = true;
	}
}

int	parse_color(char *line, t_data *data, char type)
{
	int		r;
	int		g;
	int		b;
	int		rgb_int;
	char	*color_str;

	if (!check_color_duplicate(data, type))
		return (0);
	color_str = skip_spaces(line + 1);
	if (!*color_str)
	{
		printf("Error\nMissing color values\n");
		return (0);
	}
	if (!check_comma_count(color_str) || !check_valid_chars(color_str))
		return (0);
	if (!parse_rgb(color_str, &r, &g, &b))
		return (0);
	rgb_int = rgb_to_int(r, g, b);
	store_color(data, type, rgb_int);
	return (1);
}
