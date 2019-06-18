/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:51:04 by jmondino          #+#    #+#             */
/*   Updated: 2019/06/18 18:02:51 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_timeorder(char **tab)
{
	int			j;
	int			i;
	char		*tmp;
	struct stat pStat;
	struct stat pStat2;

	i = 0;
	if (!(ft_strcmp(tab[0], "./ft_ls")))
		i++;
	while (tab[i])
	{
		lstat(tab[i], &pStat);
		j = i + 1;
		while (tab[j])
		{
			lstat(tab[j], &pStat2);
			if (pStat.st_mtime < pStat2.st_mtime)
			{
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

void	ft_asciiorder(char **tab)
{
	int		j;
	int		i;
	char	*tmp;

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

void    ft_revtab(char **tab)
{
    int     i;
    int     j;
    char    *tmp;

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

void    ft_fillpShit(char *flags, char **newav, int index, t_shit *pShit)
{
    pShit->flags = flags;
    pShit->files = ft_isfile(newav, index, pShit);
    pShit->dirs = ft_isdir(newav, index);
    if (newav[0] == NULL)
    {
		free(pShit->dirs);
		if (!(pShit->dirs = (char **)malloc(sizeof(char *) * 2)))
			return ;
        pShit->dirs[0] = ft_strdup("./");
        pShit->dirs[1] = NULL;
    }
    if (ft_iscinstr(pShit->flags, 'r'))
    {
        ft_revtab(pShit->files);
        ft_revtab(pShit->dirs);
    }
}

t_shit      *initstru(void)
{
    t_shit      *pShit;
	
    if ((pShit = malloc(sizeof(t_shit))) == NULL)
        return (NULL);
	pShit->inex = NULL;
    pShit->flags = NULL;
    pShit->files = NULL;
    pShit->dirs = NULL;
	pShit->subdir = 0;
	pShit->error = 0;
    return (pShit);
}

int get_day(char *date)
{
    int i;

    i = 0;
    while(!ft_isdigit(date[i]))
        i++;
    return (ft_atoi(date + i));
}
