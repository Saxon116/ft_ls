/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 12:06:18 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/03 10:43:04 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_accessorder(char **tab)
{
	int				j;
	int				i;
	char			*tmp;
	struct stat		pstat;
	struct stat		pstat2;

	i = -1;
	if (!(ft_strcmp(tab[0], "./ft_ls")))
		i++;
	while (tab[++i])
	{
		lstat(tab[i], &pstat);
		j = i;
		while (tab[++j])
		{
			lstat(tab[j], &pstat2);
			if (pstat.st_atime < pstat2.st_atime)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
				lstat(tab[i], &pstat);
			}
		}
	}
}

void		ft_timeorder(char **tab)
{
	int				j;
	int				i;
	char			*tmp;
	struct stat		pstat;
	struct stat		pstat2;

	i = -1;
	if (!(ft_strcmp(tab[0], "./ft_ls")))
		i++;
	while (tab[++i])
	{
		lstat(tab[i], &pstat);
		j = i;
		while (tab[++j])
		{
			lstat(tab[j], &pstat2);
			if (pstat.st_mtime < pstat2.st_mtime)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
				lstat(tab[i], &pstat);
			}
		}
	}
}

void		ft_asciiorder(char **tab)
{
	int				j;
	int				i;
	char			*tmp;

	j = 0;
	if (!(ft_strcmp(tab[0], "./ft_ls")))
		j++;
	while (tab[j])
	{
		i = j + 1;
		while (tab[i])
		{
			if (ft_strcmp(tab[i], tab[j]) < 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			i++;
		}
		j++;
	}
}

void		ft_revtab(char **tab)
{
	int				i;
	int				j;
	char			*tmp;

	i = 0;
	j = 0;
	while (tab[j])
		j++;
	j--;
	while (i < j)
	{
		tmp = tab[i];
		tab[i] = tab[j];
		tab[j] = tmp;
		i++;
		j--;
	}
}
