/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roubelka <roubelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:59:48 by roubelka          #+#    #+#             */
/*   Updated: 2026/03/05 16:59:49 by roubelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static int	parse_element(char *line, t_data *data)
{
	char	*trimmed;

	trimmed = skip_spaces(line);
	if (!trimmed)
		return (0);
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		return (parse_texture(trimmed, data, 'N'));
	if (ft_strncmp(trimmed, "SO ", 3) == 0)
		return (parse_texture(trimmed, data, 'S'));
	if (ft_strncmp(trimmed, "WE ", 3) == 0)
		return (parse_texture(trimmed, data, 'W'));
	if (ft_strncmp(trimmed, "EA ", 3) == 0)
		return (parse_texture(trimmed, data, 'E'));
	if (ft_strncmp(trimmed, "F ", 2) == 0)
		return (parse_color(trimmed, data, 'F'));
	if (ft_strncmp(trimmed, "C ", 2) == 0)
		return (parse_color(trimmed, data, 'C'));
	return (0);
}

int	parse_line(char *line, t_data *data)
{
	char	*trimmed;

	if (data->map_started)
		return (parse_map_line(line, data));
	trimmed = skip_spaces(line);
	if (is_empty_line(trimmed))
		return (1);
	if (parse_element(trimmed, data))
		return (1);
	if (data->parsed_no && data->parsed_so && data->parsed_we
		&& data->parsed_ea && data->parsed_f && data->parsed_c)
	{
		data->map_started = true;
		return (parse_map_line(line, data));
	}
	return (0);
}

static void	trim_newline(char *str)
{
	int	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r'))
	{
		str[len - 1] = '\0';
		len--;
	}
}

static int	read_and_parse(int fd, t_data *data)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		trim_newline(line);
		if (!parse_line(line, data))
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	parse_file(char *filename, t_data *data)
{
	int	fd;

	if (!check_file_ext(filename))
	{
		printf("Error\nInvalid file extension (.cub required)\n");
		return (0);
	}
	fd = open_file(filename);
	if (fd < 0)
		return (0);
	if (!read_and_parse(fd, data))
		return (0);
	if (!finalize_map(data))
		return (0);
	return (validate_data(data));
}
