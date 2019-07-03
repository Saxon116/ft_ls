/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 11:16:54 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/03 14:21:18 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_entry		*ft_tri_date(t_entry *list, t_args *pargs)
{
	t_entry		*start;
	t_entry		*lstart;
	int			swap;

	start = list;
	swap = 1;
	lstart = NULL;
	while (swap && list)
	{
		swap = 0;
		start = list;
		while (start->next != lstart)
		{
			if (start->mtime < start->next->mtime)
			{
				ft_swap(start, start->next);
				swap = 1;
			}
			start = start->next;
		}
		lstart = start;
	}
	if (ft_iscinstr(pargs->flags, 'r'))
		ft_rev_list(&list);
	return (!list ? NULL : list);
}

t_entry		*ft_tri_access(t_entry *list, t_args *pargs)
{
	t_entry		*start;
	t_entry		*lstart;
	int			swap;

	start = list;
	swap = 1;
	lstart = NULL;
	while (swap && list)
	{
		swap = 0;
		start = list;
		while (start->next != lstart)
		{
			if (start->date_accessed < start->next->date_accessed)
			{
				ft_swap(start, start->next);
				swap = 1;
			}
			start = start->next;
		}
		lstart = start;
	}
	if (ft_iscinstr(pargs->flags, 'r'))
		ft_rev_list(&list);
	return (!list ? NULL : list);
}

t_entry		*ft_tri_ascii(t_entry *list, t_args *pargs)
{
	t_entry			*start;
	t_entry			*lstart;
	int				swap;

	start = list;
	swap = 1;
	lstart = NULL;
	while (swap && list)
	{
		swap = 0;
		start = list;
		while (start->next != lstart)
		{
			if (ft_strcmp(start->name, start->next->name) > 0)
			{
				ft_swap(start, start->next);
				swap = 1;
			}
			start = start->next;
		}
		lstart = start;
	}
	if (ft_iscinstr(pargs->flags, 'r'))
		ft_rev_list(&list);
	return (!list ? NULL : list);
}

void		ft_rev_list(t_entry **list)
{
	t_entry			*curr;
	t_entry			*prev;
	t_entry			*next;

	curr = *list;
	prev = NULL;
	next = NULL;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*list = prev;
}
