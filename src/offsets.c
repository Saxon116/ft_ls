/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offsets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 14:34:22 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/02 14:37:32 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void get_special_offsets(int **offsets, t_entry *list_curr)
{
    if (S_ISBLK(list_curr->type) || S_ISCHR(list_curr->type))
    {
        if (num_length(list_curr->major) > offsets[0][5])
            offsets[0][5] = num_length(list_curr->major);
        if (num_length(list_curr->minor) > offsets[0][6])
            offsets[0][6] = num_length(list_curr->minor);
        if (num_length(list_curr->minor) + num_length(list_curr->major) >
            offsets[0][7])
            offsets[0][7] = num_length(list_curr->minor) + num_length(list_curr->major);
    }
}
int     *get_offsets(t_entry *list_start)
{
    int         *offsets;
    int    i;
    t_entry     *list_curr;

    if ((offsets = malloc(sizeof(int) * 8)) == NULL)
        return 0;
    i =0;
    while (i != 7)
    {
        offsets[i] = 0;
		i++;
    }
    list_curr = list_start;
    while (list_curr)
    {
        get_basic_offsets(&offsets, list_curr);
        get_special_offsets(&offsets, list_curr);
        list_curr = list_curr->next;
    }
    return (offsets);
}

void get_basic_offsets(int  **offsets, t_entry *list_curr)
{
    if (num_length(list_curr->hard_links) > offsets[0][0])
        offsets[0][0] = num_length(list_curr->hard_links);
    if (num_length(list_curr->size) > offsets[0][1])
        offsets[0][1] = num_length(list_curr->size);
    if (num_length(list_curr->date_day_modified) > offsets[0][2])
        offsets[0][2] = num_length(list_curr->date_day_modified);
    if (ft_strlen(list_curr->user) > (unsigned) offsets[0][3])
        offsets[0][3] = ft_strlen(list_curr->user);
    if (ft_strlen(list_curr->group) > (unsigned) offsets[0][4])
        offsets[0][4] = ft_strlen(list_curr->group);
}

int     num_length(long long num)
{
    int         i;

    i = 0;
    if (num < 0)
    {
        num = -num;
        i++;
    }
    while (num /= 10)
        i++;
    i++;
    return (i);
}
