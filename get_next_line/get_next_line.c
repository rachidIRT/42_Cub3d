/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-most <ael-most@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 06:35:08 by ael-most          #+#    #+#             */
/*   Updated: 2025/01/29 11:10:19 by ael-most         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
		return (free_lst(lst), lst = NULL, NULL);
	line = NULL;
	read_and_lst(fd, &lst);
	if (lst == NULL)
		return (NULL);
	extract_line(lst, &line);
	clean_lst(&lst);
	if (line == NULL || line[0] == '\0')
		return (free_lst(lst), lst = NULL, free(line), NULL);
	return (line);
}

void	read_and_lst(int fd, t_list **lst)
{
	char	*buf;
	int		bytes_read;

	bytes_read = 1;
	while (!found_newline(*lst) && bytes_read != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return (free_lst(*lst), *lst = NULL, (void)0);
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buf), free_lst(*lst), *lst = NULL, (void)0);
		buf[bytes_read] = '\0';
		if (bytes_read > 0)
			add_to_lst(lst, buf, bytes_read);
		free(buf);
		if (bytes_read == 0)
			break ;
	}
}

void	add_to_lst(t_list **lst, char *buf, int bytes_read)
{
	int		i;
	t_list	*last;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return (free_lst(*lst), *lst = NULL, (void)0);
	new_node->next = NULL;
	new_node->content = malloc(bytes_read + 1);
	if (new_node->content == NULL)
		return (free(new_node), (void)0);
	i = 0;
	while (buf[i] && i < bytes_read)
	{
		new_node->content[i] = buf[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*lst == NULL)
		return (*lst = new_node, (void)0);
	last = ft_lst_get_last(*lst);
	last->next = new_node;
}

void	extract_line(t_list *lst, char **line)
{
	int	i;
	int	j;

	if (lst == NULL)
		return ;
	generate_line(line, lst);
	if (*line == NULL)
		return ;
	j = 0;
	while (lst)
	{
		i = 0;
		while (lst->content[i])
		{
			if (lst->content[i] == '\n')
			{
				(*line)[j++] = lst->content[i];
				break ;
			}
			(*line)[j++] = lst->content[i++];
		}
		lst = lst->next;
	}
	(*line)[j] = '\0';
}

void	clean_lst(t_list **lst)
{
	t_list	*last;
	t_list	*new;
	int		i;
	int		j;

	if (!lst || !*lst)
		return ;
	i = ((j = 0), (last = ft_lst_get_last(*lst)), 0);
	if (!last)
		return ;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] == '\n')
		i++;
	if (!last->content[i])
		return (free_lst(*lst), *lst = NULL, (void)0);
	new = malloc(sizeof(t_list));
	if (!new)
		return (free_lst(*lst), *lst = NULL, (void)0);
	new->content = malloc(ft_strlen(last->content) - i + 1);
	if (!new->content)
		return (free(new), free_lst(*lst), *lst = NULL, (void)0);
	while (last->content[i])
		new->content[j++] = last->content[i++];
	new->content[j] = (new->next = NULL, free_lst(*lst), *lst = new, '\0');
}
