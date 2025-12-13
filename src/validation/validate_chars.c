/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roubelka <roubelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 23:00:44 by roubelka          #+#    #+#             */
/*   Updated: 2025/12/09 00:35:07 by roubelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

int is_valid_map_char(char c)
{
    if (c == '0' || c == '1' || c == ' ')
        return (1);
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
        return (1);
    // DEBUG: Print invalid character
    printf("Invalid char: '%c' (ASCII: %d)\n", c, (int)c);
    return (0);
}

int is_player_char(char c)
{
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
        return (1);
    return (0);
}

int is_walkable(char c)
{
    if (c == '0')
        return (1);
    if (is_player_char(c))
        return (1);
    return (0);
}