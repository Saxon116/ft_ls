/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 14:03:11 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/02 16:44:01 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_display(t_args *pargs)
{
	int				i;
	t_entry			*files_lst;

	i = -1;
	if (ft_iscinstr(pargs->flags, 'l') || ft_iscinstr(pargs->flags, 'g'))
	{
		while (pargs->files[++i])
		{
			files_lst = add_new_entry(pargs->files[i], pargs->files[i], pargs);
			display_entries_l(files_lst, pargs, pargs->files[i]);
		}
	}
	else
		display_normally(pargs, i);
	if (pargs->files[0] && pargs->dirs[0])
		printf("\n");
	i = 0;
	while (pargs->dirs[i])
	{
		list_dir_recursive(pargs->dirs[i], pargs->dirs[i], pargs);
		i++;
		if (pargs->dirs[i])
			printf("\n");
	}
}

void		display_normally(t_args *pargs, int i)
{
	t_entry			*start;
	t_entry			*browse;

	browse = NULL;
	start = browse;
	while (pargs->files[++i])
	{
		if (!browse)
		{
			browse = add_new_entry(pargs->files[i], pargs->files[i], pargs);
			start = browse;
		}
		else
		{
			browse->next = add_new_entry(pargs->files[i],
										pargs->files[i], pargs);
			browse = browse->next;
		}
	}
	if (start)
		ft_print_column(start);
}

void		ft_display_d(t_args *pargs)
{
	t_entry			*entries;

	entries = fill_list_d(pargs);
	if (entries)
	{
		if (ft_iscinstr(pargs->flags, 'l') || ft_iscinstr(pargs->flags, 'g'))
			display_entries_l(entries, pargs, pargs->newav[0]);
		else
			ft_print_column(entries);
	}
	lstdel(&entries);
}
