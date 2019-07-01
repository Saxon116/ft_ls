/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 12:02:51 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/01 10:39:24 by jmondino         ###   ########.fr       */
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
	lstdel(&entries);
}

void	ft_accessorder(char **tab)
{
	int         j;
    int         i;
    char        *tmp;
    struct stat pStat;
    struct stat pStat2;

    i = -1;
    if (!(ft_strcmp(tab[0], "./ft_ls")))
        i++;
    while (tab[++i])
    {
        lstat(tab[i], &pStat);
        j = i;
        while (tab[++j])
        {
            lstat(tab[j], &pStat2);
            if (pStat.st_atime < pStat2.st_atime)
            {
                tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
                lstat(tab[i], &pStat);
            }
        }
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
