/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 12:02:51 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/02 12:16:37 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
