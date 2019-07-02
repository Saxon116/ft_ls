/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:49:13 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/02 14:07:44 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void    ft_print_column(t_entry *list_start)
{
    unsigned int all_names_length;
    unsigned int list_size;
    unsigned int terminal_width;
    int columns;
    int *column_widths;
    char **str_array;
    struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    terminal_width = w.ws_col;
    all_names_length = get_all_names_length(list_start);
    list_size = get_list_size(list_start);
    columns = num_of_columns(list_start, terminal_width);
    str_array = array_from_list(list_start);
    if (all_names_length + list_size * 2  > terminal_width)
    {
        column_widths = get_column_widths(str_array, columns, list_size);
        print_rows(str_array, column_widths, columns, list_start);
        free(column_widths);
    }
    else
        print(list_start);
    free_columns(str_array);
}

int     *get_column_widths(char **str_array, int num_of_columns, int list_size)
{
    int             *column_widths;
    int             per_column;
    int             i;

    per_column = list_size / (num_of_columns == 0 ? 1 : num_of_columns) + 1;
    i = 0;
    if ((column_widths = malloc(sizeof(int) * list_size)) == NULL)
        return (0);
    while (i < num_of_columns)
    {
        column_widths[i] = longest_in_column(str_array, i * per_column,
                                             i * per_column + per_column, list_size);
        i++;
    }
    return (column_widths);
}

int     longest_in_column(char **str_array, int start, int end, int list_size)
{
    int             i;
    unsigned int    longest_name;

    longest_name = 0;
    i = start;
    while (i < list_size && str_array[i] && i < end)
    {
        if (ft_strlen(str_array[i]) > longest_name)
            longest_name = ft_strlen(str_array[i]);
        i++;
    }
    return (longest_name);
}

int     num_of_columns(t_entry *list_start, int terminal_width)
{
    int longest_entries[get_list_size(list_start)];
    t_entry *list_curr;
    int i;
    int n;
    int spaces;

    list_curr = list_start;
    n = get_list_size(list_start);
    spaces = 0;
    i = 0;
    while (list_curr)
    {
        longest_entries[i] = ft_strlen(list_curr->name);
        list_curr = list_curr->next;
        i++;
    }
    sort_longest_entries(n, longest_entries);
    i = 0;
    spaces += longest_entries[i] + 2;
    while (spaces < terminal_width)
    {
        i++;
        spaces += longest_entries[i] + 2;
    }
    return (i == 0 ? 1 : i);
}

void print_rows(char **str_array, int *column_widths, int columns, t_entry *list_start)
{
    int i;
    int j;
    int per_column;

    i = 0;
    j = 0;
    per_column = get_list_size(list_start) / columns + 1;
    while (i < per_column)
    {
        j = 0;
        while (j < columns)
        {
            print_row_entries(list_start, i + (j * (per_column)),
							  str_array, column_widths[j]);
			j++;
        }
        printf("\n");
        i++;
    }
}
