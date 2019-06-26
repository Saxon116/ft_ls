/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 12:02:51 by jmondino          #+#    #+#             */
/*   Updated: 2019/06/26 18:25:35 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_display_d(t_shit *pShit)
{
	t_entry		*entries;

	entries = fill_list_d(pShit);
	if (entries)
	{
		if (ft_iscinstr(pShit->flags, 'l') || ft_iscinstr(pShit->flags, 'g'))
		   	display_entries_l(entries, pShit, pShit->newav[0]);
		else
			ft_print_column(entries);
	}
}

t_entry		*fill_list_d(t_shit *pShit)
{
	t_entry		*start;
	t_entry		*browse;
	int			i;

	i = -1;
	browse = NULL;
	start = browse;
	if (pShit->dsfs[0])
	{
		while (pShit->dsfs[++i])
		{
			if (!browse)
			{
				browse = add_new_entry(pShit->dsfs[i], pShit->dsfs[i], pShit);
				start = browse;
			}
			else
			{
				browse->next = add_new_entry(pShit->dsfs[i], pShit->dsfs[i], pShit);
				browse = browse->next;
			}
		}
	}
	else
	{
		browse = add_new_entry(".", ".", pShit);
		start = browse;
	}
	return (start);
}
