/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 12:02:51 by jmondino          #+#    #+#             */
/*   Updated: 2019/06/25 13:11:05 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_display_d(t_shit *pShit)
{
	t_entry		*entries;

	entries = fill_list_d(pShit);
	if (entries)
	{
		if (ft_iscinstr(pShit->flags, 'l'))
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
	if (pShit->newav[0])
	{
		while (pShit->newav[++i])
		{
			printf("%s\n", pShit->newav[i]);
			if (!browse)
			{
				browse = add_new_entry(pShit->newav[i], pShit->newav[i]);
				start = browse;
			}
			else
			{
				browse->next = add_new_entry(pShit->newav[i], pShit->newav[i]);
				browse = browse->next;
			}
		}
	}
	else
	{
		browse = add_new_entry(".", ".");
		start = browse;
	}
	return (start);
}
