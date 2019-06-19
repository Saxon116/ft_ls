/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 18:26:06 by jmondino          #+#    #+#             */
/*   Updated: 2019/06/19 18:27:15 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void print_rows(char **str_array, int *column_widths, int columns, t_entry *list_start)
{
    int i;
    int j;
    int length;
    int per_column;
    t_entry *browse;

    browse = list_start;
    i = 0;
    j = 0;
    length = 0;
    per_column = get_list_size(list_start) / columns + 1;
    while (str_array[length])
        length++;
    while (i < per_column)
    {
        j = 0;
        while (j < columns)
        {
            if (i + (j * (per_column)) < length
				&& str_array[i + (j * (per_column))])
            {
                while (ft_strcmp(browse->name, str_array[i + (j * (per_column))]))
                    browse = browse->next;
                print_color(str_array[i + (j * (per_column))], browse->type, browse->rights);
                print_spaces(column_widths[j] -
							 ft_strlen(str_array[i + (j * (per_column))]));
                browse = list_start;
            }
            j++;
        }
        printf("\n");
        i++;
    }
}

void    ft_print_column(t_entry *list_start)
{
    unsigned int all_names_length;
    unsigned int list_size;
    unsigned int terminal_width;
    int columns;
    char **str_array;
    t_entry *list_current;
    struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    terminal_width = w.ws_col;
    all_names_length = 0;
    list_size = get_list_size(list_start);
    columns = num_of_columns(list_start, terminal_width);
    list_current = list_start;
    str_array = array_from_list(list_start);
    while (list_current)
    {
        all_names_length += ft_strlen(list_current->name);
        list_current = list_current->next;
    }
    if (all_names_length + list_size * 2  > terminal_width)
    {
        int *column_widths = get_column_widths(str_array,
											   columns, list_size);
        print_rows(str_array, column_widths, columns, list_start);
        free(column_widths);
    }
    else
        print_normally(list_start);
    int i = 0;
    while (str_array[i])
    {
        free(str_array[i]);
        i++;
    }
    free(str_array);
}
