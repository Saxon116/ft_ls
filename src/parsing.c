/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:32:58 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/02 13:32:59 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_parseargs(char **av, t_args *pargs)
{
	int				j;
	char			*tmp;

	j = 0;
	tmp = NULL;
	j = fill_newav(av, pargs, &tmp, j);
	if (pargs->newav[0] && !ft_iscinstr(tmp, 'f'))
	{
		ft_asciiorder(pargs->newav);
		if (ft_iscinstr(tmp, 't'))
		{
			if (ft_iscinstr(tmp, 'u'))
				ft_accessorder(pargs->newav);
			else
				ft_timeorder(pargs->newav);
		}
	}
	ft_fillpargs(tmp, pargs->newav, j, pargs);
}

char	**ft_isdir(char **newav, int index)
{
	char			**tab;
	int				i;
	int				j;

	if (newav == NULL)
		return (NULL);
	if (!(tab = malloc((index + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	j = 0;
	while (newav[i])
	{
		if (ft_strcmp(newav[i],  "--"))
		{
			if (ft_existent2(newav[i]))
			{
				tab[j] = ft_strdup(newav[i]);
				j++;
			}
		}
		i++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_isfile(char **newav, int index, t_args *pargs)
{
	char			**tab;
	int				i;
	int				j;

	if (newav == NULL)
		return (NULL);
	if (!(tab = malloc((index + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	j = 0;
	while (newav[i])
	{
		if (ft_strcmp(newav[i],  "--"))
		{
			if (ft_existent(newav[i], pargs))
			{
				tab[j] = ft_strdup(newav[i]);
				j++;
			}
		}
		i++;
	}
	tab[j] = NULL;
	return (tab);
}

int		ft_existent(char *str, t_args *pargs)
{
	struct stat		pstat;

	if (lstat(str, &pstat))
	{
		printf("ft_ls: %s: No such file or directory\n", str);
		pargs->error++;
		return (0);
	}
	if (S_ISREG(pstat.st_mode)
		|| S_ISLNK(pstat.st_mode)
		|| S_ISBLK(pstat.st_mode)
		|| S_ISFIFO(pstat.st_mode)
		|| S_ISCHR(pstat.st_mode)
		|| S_ISSOCK(pstat.st_mode))
		return (1);
	return (0);
}

int		ft_existent2(char *str)
{
	struct stat		pstat;
	char			*link;

	if (lstat(str, &pstat))
		return (0);
	if (S_ISDIR(pstat.st_mode))
		return (1);
	if (S_ISLNK(pstat.st_mode))
	{
		link = get_link_path(str);
		lstat(link, &pstat);
		if (S_ISDIR(pstat.st_mode))
			return (1);
	}
	return (0);
}
