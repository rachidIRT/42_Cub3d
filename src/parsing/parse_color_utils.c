#include "../../include/header.h"

int	check_comma_count(char *str)
{
	int	count;
	int	i;

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
		printf("Error\nInvalid color format (need exactly 2 commas)\n");
		return (0);
	}
	return (1);
}

int	check_valid_chars(char *str)
{
	int	i;

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

int	validate_rgb(int r, int g, int b)
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
