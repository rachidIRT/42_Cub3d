#include "../../include/header.h"

int	count_map_lines(t_map_line *head)
{
	int	total;

	total = 0;
	while (head)
	{
		total++;
		head = head->next;
	}
	return (total);
}

int	get_max_width(t_map_line *head)
{
	int	max_width;
	int	current_len;

	max_width = 0;
	while (head)
	{
		current_len = ft_strlen(head->line);
		if (current_len > max_width)
			max_width = current_len;
		head = head->next;
	}
	return (max_width);
}

void	copy_and_pad_line(char *dest, char *src, int max_width)
{
	int	i;
	int	src_len;

	src_len = ft_strlen(src);
	i = 0;
	while (i < src_len)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < max_width)
	{
		dest[i] = ' ';
		i++;
	}
	dest[i] = '\0';
}

int	fill_grid_rows(t_data *data)
{
	t_map_line	*cur;
	int			row;

	cur = data->map_lines;
	row = 0;
	while (cur)
	{
		data->map.grid[row] = malloc(data->map.width + 1);
		if (!data->map.grid[row])
		{
			printf("Error\nFailed to allocate map row\n");
			return (0);
		}
		copy_and_pad_line(data->map.grid[row], cur->line,
			data->map.width);
		cur = cur->next;
		row++;
	}
	data->map.grid[row] = NULL;
	return (1);
}
