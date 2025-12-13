/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roubelka <roubelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:51:04 by roubelka          #+#    #+#             */
/*   Updated: 2025/12/07 23:37:44 by roubelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

int check_file_ext(char *filename)
{
    int line;

    if (!filename)
        return (0);
    line = ft_strlen(filename);
    if (line < 5)
        return (0);
    if(ft_strncmp(filename + line - 4, ".cub", 4) != 0)
        return (0);
    return (1);        
}
int check_file_exists(char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (0);
    close(fd);
    return (1);
}

int open_file(char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        printf("Error\nCannot open file");
        return (0);
    }
    return (fd);
}