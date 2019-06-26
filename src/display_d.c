/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 12:02:51 by jmondino          #+#    #+#             */
/*   Updated: 2019/06/26 19:33:42 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_display_d(t_shit *pShit)
{
	t_entry		*entries;

	/*ft_asciiorder(pShit->dsfs);
	if (ft_iscinstr(pShit->flags, 't'))
	{
		printf("here  :  ");
		if (ft_iscinstr(pShit->flags, 'u'))
            ft_accessorder(pShit->dsfs);
		ft_timeorder(pShit->dsfs);
		}*/
	entries = fill_list_d(pShit);
	if (entries)
	{
		if (ft_iscinstr(pShit->flags, 'l') || ft_iscinstr(pShit->flags, 'g'))
		   	display_entries_l(entries, pShit, pShit->newav[0]);
		else
			ft_print_column(entries);
	}
}

void	ft_accessorder(char **tab)
{
	int         j;
    int         i;
    char        *tmp;
    struct stat pStat;
    struct stat pStat2;

    i = 0;
    if (!(ft_strcmp(tab[0], "./ft_ls")))
        i++;
	while (tab[i])
	{
		lstat(tab[i], &pStat);
		printf("[%s] : %ld\n", tab[i], pStat.st_atime);
		i++;
	}
	i = 0;
    while (tab[i])
    {
        lstat(tab[i], &pStat);
        j = i + 1;
        while (tab[j])
        {
            lstat(tab[j], &pStat2);
            if (pStat.st_atime < pStat2.st_atime)
            {
				printf("here\n");
                tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
                lstat(tab[i], &pStat);
            }
            j++;
        }
        i++;
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
