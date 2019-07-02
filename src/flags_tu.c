/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_tu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 12:22:34 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/02 12:03:53 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_swap(t_entry *a, t_entry *b)
{
	t_entry		*tmp;

	if (!(tmp = malloc(sizeof(t_entry))))
		return ;
	ft_fill(tmp, a);
	ft_fill(a, b);
	ft_fill(b, tmp);
	free(tmp);
}

void		ft_fill(t_entry *fill, t_entry *src)
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
	fill->minor = src->minor;
	fill->major = src->major;
}
