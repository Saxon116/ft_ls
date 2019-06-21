/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 12:02:51 by jmondino          #+#    #+#             */
/*   Updated: 2019/06/21 16:48:16 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_display_d(t_shit *pShit)
{
	t_entry		*entries;

	entries = fill_list_d(pShit);
	if (entries)
		ft_print_column(entries);
}

t_entry		*fill_list_d(t_shit *pShit)
{
	t_entry		*start;
	t_entry		*browse;
	int			i;
	
	i = -1;
	browse = NULL;
	start = browse;
	if (pShit->files[0])
	{
		while (pShit->files[++i])
		{
			if (!browse)
			{
				browse = add_new_entry(pShit->files[i], pShit->files[i]);
				start = browse;
			}
			else
			{
				browse->next = add_new_entry(pShit->files[i], pShit->files[i]);
				browse = browse->next;
			}
		}
	}
	if (pShit->dirs[0])
	{
		while (pShit->dirs[++i])
		{
			if (!browse)
			{
				browse = add_new_entry(pShit->dirs[i], pShit->dirs[i]);
				start = browse;
			}
			else
			{
				browse->next = add_new_entry(pShit->dirs[i], pShit->dirs[i]);
				browse = browse->next;
			}
		}
	}
	return (start);
}
