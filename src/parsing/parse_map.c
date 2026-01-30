

#include "../../include/header.h"

void    add_map_line(t_data *data, char *line)
{
        t_map_line  *new;
    t_map_line  *current;

    new = malloc(sizeof(t_map_line));
    if (!new)
        return ;
    
    new->line = ft_strdup(line);
    // new->line = line; // hada zidto ohaydto
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
// Count how many lines in the map
int count_map_lines(t_map_line *head)
{
    int total;
    
    total = 0;
    while(head)
    {
        total++;
        head = head->next;
    }
    return (total);
}
// Find the longest line in the map
int get_max_width(t_map_line *head)
{
    int max_width;
    int current_len;
    
    max_width = 0;
    while(head)
    {
        current_len = ft_strlen(head->line);
        if (current_len > max_width)
            max_width = current_len;
          head = head->next;
    }
    return (max_width);
}
// Copy a line and pad it with spaces if needed
static void copy_and_pad_line(char *dest, char *src, int max_width)
{
    int i;
    int src_len;

    src_len = ft_strlen(src);
    i = 0;
    // Copy original characters
    while (i < src_len)
    {
        dest[i] = src[i];
        i++;
    }
    // idaft spase hta twsal max_width
    while(i < max_width)
    {
        dest[i] = ' ';
        i++;
    }
    dest[i] = '\0';
}
int parse_map_line(char *line, t_data   *data)
{
    if (!data->parsed_no || !data->parsed_ea ||
        !data->parsed_so || !data->parsed_we ||
        !data->parsed_c || !data->parsed_f)
    {
        printf("Error\nMap must come after all elements\n");
        return (0);
    }
    // Skip empty lines before map starts
    if (is_empty_line(line) && !data->map_lines)
        return (1);
    
    // Add line to temporary storage
    add_map_line(data, line);
    return (1);
}

int finalize_map(t_data *data)
{
    t_map_line  *current_line;
    int         row;
    // Check we have map lines
    if (!data->map_lines)
    {
        printf("Error\nNo map found\n");
        return (0);
    }
    // Calculate map dimensions
    data->map.height = count_map_lines(data->map_lines);
    data->map.width = get_max_width(data->map_lines);
    // Allocate array of row pointers (+1 for NULL terminator)
    data->map.grid = ft_calloc(data->map.height + 1, sizeof(char *));
    if (!data->map.grid)
    {
        printf("Error\nFailed to allocate map grid\n");
        return (0);
    }
    // Process each line from linked list
    current_line = data->map_lines;
    row = 0;
    while (current_line)
    {
        // Allocate space for this row (+1 for '\0')
        data->map.grid[row] = malloc(data->map.width + 1);
        if (!data->map.grid[row])
        {
            printf("Error\nFailed to allocate map row\n");
            return (0);
        }
        
        // Copy line and pad with spaces to max_width
        copy_and_pad_line(data->map.grid[row], current_line->line, data->map.width);
        
        // Move to next line
        current_line = current_line->next;
        row++;
    }
    // NULL terminate the array
    data->map.grid[row] = NULL;
    
    return (1);
}