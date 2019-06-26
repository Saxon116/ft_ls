/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_collumn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 18:27:25 by jmondino          #+#    #+#             */
/*   Updated: 2019/06/26 13:36:30 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		*get_column_widths(char **str_array, int num_of_columns, int list_size)
{
    int *column_widths;
    int per_column;
    int i;

    per_column = list_size / (num_of_columns == 0 ? 1 : num_of_columns) + 1;
    i = 0;
    if ((column_widths = malloc(sizeof(int) * list_size)) == NULL)
        return 0;
    while (i < num_of_columns)
    {
        column_widths[i] = longest_in_column(str_array,
											 i * per_column, i * per_column + per_column, list_size);
        i++;
    }
    return (column_widths);
}

int 	longest_in_column(char **str_array, int start, int end, int list_size)
{
    int i;
    unsigned int longest_name;

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
