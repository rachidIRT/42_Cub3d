#include "../../include/header.h"

int	is_surrounded_by_walls(t_data *data, int y, int x)
{
	if (y == 0 || y == data->map.height - 1)
		return (0);
	if (x == 0 || x == data->map.width - 1)
		return (0);
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

static void	scan_for_player(t_data *data, int *count)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			c = data->map.grid[i][j];
			if (is_player_char(c))
			{
				(*count)++;
				data->player.pos_x = j + 0.5;
				data->player.pos_y = i + 0.5;
				data->player.direction = c;
			}
			j++;
		}
		i++;
	}
}

int	find_player(t_data *data)
{
	int	player_count;

	player_count = 0;
	scan_for_player(data, &player_count);
	if (player_count == 0)
	{
		printf("Error\nNo player found in map\n");
		return (0);
	}
	if (player_count > 1)
	{
		printf("Error\nMultiple players found in map\n");
		return (0);
	}
	return (1);
}

int	validate_map(t_data *data)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			c = data->map.grid[i][j];
			if (!is_valid_map_char(c))
				return (printf("Error\nInvalid character in map\n"), 0);
			if (is_walkable(c))
			{
				if (!is_surrounded_by_walls(data, i, j))
					return (printf("Error\nMap is not closed by walls\n"), 0);
			}
			j++;
		}
		i++;
	}
	return (find_player(data));
}

int	validate_data(t_data *data)
{
	if (!data->textures.north || !data->textures.east
		|| !data->textures.south || !data->textures.west)
	{
		printf("Error\nMissing texture(s)\n");
		return (0);
	}
	if (data->colors.ceiling == -1)
	{
		printf("Error\nMissing ceiling color\n");
		return (0);
	}
	if (data->colors.floor == -1)
	{
		printf("Error\nMissing floor color\n");
		return (0);
	}
	if (!data->map.grid)
	{
		printf("Error\nMissing map\n");
		return (0);
	}
	if (!validate_map(data))
		return (0);
	return (1);
}
