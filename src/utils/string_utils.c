#include "../../include/header.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

char	*skip_spaces(char *str)
{
	if (!str)
		return (NULL);
	while (*str && ft_isspace(*str))
		str++;
	return (str);
}

int	is_empty_line(char *line)
{
	if (!line)
		return (1);
	while (*line)
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*trim_line(char *line)
{
	char	*start;
	char	*end;
	char	*trmid;
	int		len;
	int		i;

	if (!line)
		return (NULL);
	start = skip_spaces(line);
	if (!start)
		return (ft_strdup(""));
	end = start + ft_strlen(start) - 1;
	while (end > start && ft_isspace(*end))
		end--;
	len = end - start + 1;
	trmid = malloc(len + 1);
	if (!trmid)
		return (NULL);
	i = 0;
	while (i < len)
	{
		trmid[i] = start[i];
		i++;
	}
	return (trmid[i] = '\0', trmid);
}
