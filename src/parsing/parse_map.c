#include "../../include/header.h"

void	add_map_line(t_data *data, char *line)
{
	t_map_line	*new;
	t_map_line	*current;

	new = malloc(sizeof(t_map_line));
	if (!new)
		return ;
	new->line = ft_strdup(line);
	new->next = NULL;
	if (!data->map_lines)
	{
		data->map_lines = new;
		return ;
	}
	current = data->map_lines;
	while (current->next)
		current = current->next;
	current->next = new;
}

int	parse_map_line(char *line, t_data *data)
{
	if (!data->parsed_no || !data->parsed_ea
		|| !data->parsed_so || !data->parsed_we
		|| !data->parsed_c || !data->parsed_f)
	{
		printf("Error\nMap must come after all elements\n");
		return (0);
	}
	if (is_empty_line(line) && !data->map_lines)
		return (1);
	add_map_line(data, line);
	return (1);
}

int	finalize_map(t_data *data)
{
	if (!data->map_lines)
	{
		printf("Error\nNo map found\n");
		return (0);
	}
	data->map.height = count_map_lines(data->map_lines);
	data->map.width = get_max_width(data->map_lines);
	data->map.grid = ft_calloc(data->map.height + 1, sizeof(char *));
	if (!data->map.grid)
	{
		printf("Error\nFailed to allocate map grid\n");
		return (0);
	}
	return (fill_grid_rows(data));
}
