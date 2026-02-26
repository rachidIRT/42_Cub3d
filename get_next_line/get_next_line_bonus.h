/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-most <ael-most@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 07:12:23 by ael-most          #+#    #+#             */
/*   Updated: 2025/01/24 09:51:34 by ael-most         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
void				read_and_lst(int fd, t_list **lst);
void				add_to_lst(t_list **lst, char *buf, int bytes_read);
void				extract_line(t_list *lst, char **line);
void				clean_lst(t_list **lst);
int					found_newline(t_list *lst);
t_list				*ft_lst_get_last(t_list *lst);
void				generate_line(char **line, t_list *lst);
void				free_lst(t_list *lst);
int					ft_strlen(const char *str);

#endif
