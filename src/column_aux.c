/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 14:05:44 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/02 14:31:19 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int get_all_names_length(t_entry *list_start)
{
    int all_names_length;

    all_names_length = 0;
    while (list_start)
    {
        all_names_length += ft_strlen(list_start->name);
        list_start = list_start->next;
    }
    return (all_names_length);
}

int     get_list_size(t_entry *list_start)
{
    int             size;

    size = 0;
    while (list_start)
    {
        size++;
        list_start = list_start->next;
    }
    return (size);
}

void sort_longest_entries(int n, int *longest_entries)
{
    int i;
    int j;
    int a;

    i = 0;
    j = 0;
    a = 0;
    while (i < n)
    {
        j = i + 1;
        while (j < n)
        {
            if (longest_entries[i] < longest_entries[j])
            {
                a = longest_entries[i];
                longest_entries[i] = longest_entries[j];
                longest_entries[j] = a;
            }
            j++;
        }
        i++;
    }
}

char    **array_from_list(t_entry *list_start)
{
    char    **array;
    int     i;

    i = 0;
    if ((array = malloc((get_list_size(list_start) + 1) * sizeof(char*)))
        == NULL)
        return (0);
    while (list_start)
    {
        array[i] = ft_strdup(list_start->name);
        i++;
        list_start = list_start->next;
    }
    array[i] = NULL;
    return (array);
}

void print_row_entries(t_entry *list_start, int ijpercol, char **str_array, int column_widths_j)
{
    t_entry *browse;
    int length;

    browse = list_start;
    length = 0;
    while (str_array[length])
        length++;
    if (ijpercol < length
        && str_array[ijpercol])
    {
        while (ft_strcmp(browse->name, str_array[ijpercol]))
            browse = browse->next;
        print_color(str_array[ijpercol], browse->type, browse->rights);
        print_spaces(column_widths_j - ft_strlen(str_array[ijpercol]));
        browse = list_start;
    }
}
