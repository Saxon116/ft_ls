/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_tu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 12:22:34 by jmondino          #+#    #+#             */
/*   Updated: 2019/06/24 17:06:23 by jmondino         ###   ########.fr       */
/*   Updated: 2019/06/20 18:20:58 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_entry     *ft_tri_date(t_entry *list, t_shit *pShit)
{
    t_entry		*start;
    t_entry 	*lstart;
    t_entry 	*fresh;

    if (list == NULL)
        return NULL;
    start = list;
    fresh = start;
	while (start)
	{
		printf("[%s]\n", start->name);
		start = start->next;
	}
	start = list;
    while (start)
    {
        lstart = start->next;
        while (lstart)
        {
            if (start->mtime < lstart->mtime)
			{
				printf("[%s] <-> [%s]\n", start->name, lstart->name);
                ft_swap(start, start->next);
			}
			lstart = lstart->next;
        }
        start = start->next;
    }
	if (ft_iscinstr(pShit->flags, 'r'))
		ft_rev_list(&list);
	fresh = list;
    return fresh;
}

t_entry		*ft_tri_access(t_entry *list, t_shit *pShit)
{
    t_entry 	*start;
    t_entry 	*lstart;
    t_entry 	*fresh;

    if (list == NULL)
        return NULL;
    start = list;
    fresh = start;
	while (start)
	{
		lstart = start->next;
		while (lstart)
		{
			if (start->date_accessed < lstart->date_accessed)
				ft_swap(start, lstart);
			lstart = lstart->next;
		}
		start = start->next;
	}
	if (ft_iscinstr(pShit->flags, 'r'))
        ft_rev_list(&list);
    fresh = list;
    return fresh;
}

void    ft_swap(t_entry *a, t_entry *b)
{
    t_entry     *tmp;

    tmp = fill_tmp();
    ft_fill(tmp, a);
    ft_fill(a, b);
    ft_fill(b, tmp);
    free(tmp);
}

t_entry     *fill_tmp(void)
{
    t_entry     *tmp;

    if (!(tmp = malloc(sizeof(t_entry))))
        return NULL;
    tmp->type = 0;
    tmp->name = NULL;
    tmp->rights = NULL;
    tmp->hard_links = 0;
    tmp->user = NULL;
    tmp->group = NULL;
    tmp->size = 0;
    tmp->block_size = 0;
    tmp->date_month_modified = NULL;
    tmp->date_day_modified = 0;
    tmp->date_time_modified = NULL;
    tmp->date_accessed = 0;
    tmp->link_path = NULL;
    tmp->next = NULL;
    tmp->mtime = 0;
	tmp->has_xattr = 0;
	tmp->has_acl = 0;
	tmp->xattr = NULL;
	tmp->xattr_sizes = NULL;
    return (tmp);
}

void    ft_fill(t_entry *fill, t_entry *src)
{
    fill->type = src->type;
    fill->name = src->name;
    fill->rights = src->rights;
    fill->hard_links = src->hard_links;
    fill->user = src->user;
    fill->group = src->group;
    fill->size = src->size;
    fill->block_size = src->block_size;
    fill->date_month_modified = src->date_month_modified;
    fill->date_day_modified = src->date_day_modified;
    fill->date_time_modified = src->date_time_modified;
    fill->date_accessed = src->date_accessed;
    fill->link_path = src->link_path;
    fill->mtime = src->mtime;
	fill->has_xattr = src->has_xattr;
	fill->has_acl = src->has_acl;
	fill->xattr = src->xattr;
	fill->xattr_sizes = src->xattr_sizes;
}
