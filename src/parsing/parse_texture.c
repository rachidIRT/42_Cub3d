/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roubelka <roubelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:00:02 by roubelka          #+#    #+#             */
/*   Updated: 2026/03/05 17:00:03 by roubelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static int	check_duplicate(t_data *data, char direction)
{
	if (direction == 'N' && data->parsed_no)
	{
		printf("Error\nDuplicate NO texture\n");
		return (0);
	}
	if (direction == 'S' && data->parsed_so)
	{
		printf("Error\nDuplicate SO texture\n");
		return (0);
	}
	if (direction == 'W' && data->parsed_we)
	{
		printf("Error\nDuplicate WE texture\n");
		return (0);
	}
	if (direction == 'E' && data->parsed_ea)
	{
		printf("Error\nDuplicate EA texture\n");
		return (0);
	}
	return (1);
}

int	store_texture(t_data *data, char *path, char direction)
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

static char	*get_texture_path(char *line)
{
	char	*trimmed;
	char	*path;
	int		i;

	i = 2;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
	{
		printf("Error\nMissing texture path\n");
		return (NULL);
	}
	trimmed = trim_line(&line[i]);
	if (!trimmed)
		return (NULL);
	if (!check_file_exists(trimmed))
	{
		printf("Error\nTexture file not found\n");
		free(trimmed);
		return (NULL);
	}
	path = ft_strdup(trimmed);
	free(trimmed);
	return (path);
}

int	parse_texture(char *line, t_data *data, char direction)
{
	char	*path;

	if (!check_duplicate(data, direction))
		return (0);
	path = get_texture_path(line);
	if (!path)
		return (0);
	return (store_texture(data, path, direction));
}
