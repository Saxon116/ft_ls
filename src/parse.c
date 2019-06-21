/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:09:09 by jmondino          #+#    #+#             */
/*   Updated: 2019/06/21 12:02:39 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_parseargs(char **av, t_shit *pShit)
{
	int		i;
	int		j;
	int		bool;
	char	*tmp;
	char	*newav[255];

	i = 0;
	j = 0;
	bool = 0;
	tmp = NULL;
	while (av[++i])
	{
		if (!(ft_strcmp(av[i],  "--")) || av[i][0] != '-')
			bool = 1;
		if ((av[i][0] == '-' && av[i][1]) && bool == 0)
			tmp = ft_strjoin(tmp, ft_checkflags(av[i]));
		else
			if (ft_strcmp(av[i], "--"))
				newav[j++] = av[i];
	}
	newav[j] = NULL;
	if (newav[0])
	{
		ft_asciiorder(newav);
		if (ft_iscinstr(tmp, 't'))
			ft_timeorder(newav);
	}
	ft_fillpShit(tmp, newav, j, pShit);
}

char	**ft_isdir(char **newav, int index)
{
	char	**tab;
	int		i;
	int		j;

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

char	**ft_isfile(char **newav, int index, t_shit *pShit)
{
	char	**tab;
	int		i;
	int		j;

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
			if (ft_existent(newav[i], pShit))
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

int		ft_existent(char *str, t_shit *pShit)
{
	struct	stat	pStat;
	
	if (lstat(str, &pStat))
	{
		printf ("ft_ls: %s: No such file or directory\n", str);
		pShit->error++;
		return (0);
	}
	if (S_ISREG(pStat.st_mode) || S_ISLNK(pStat.st_mode))
		return (1);
	return (0);
}

int		ft_existent2(char *str)
{
	struct	stat	pStat;
	char			*link;

	if (lstat(str, &pStat))
		return (0);
	if (S_ISDIR(pStat.st_mode))
		return (1);
	if (S_ISLNK(pStat.st_mode))
	{
		link = get_link_path(str);
		lstat(link, &pStat);
		if (S_ISDIR(pStat.st_mode))
			return (1);
	}
	return (0);
}

char	*ft_checkflags(char *str)
{
	int		i;
	char	*tmp;

	i = 1;
	while(str[i])
	{
		if (str[i] != 'a' && str[i] != 'r' && str[i] != 'l' && str[i] != 'R'
			&& str[i] != 't' && str[i] != 'u' && str[i] != '@' && str[i] != 'g'
			&& str[i] != 'd')
		{
			printf("ft_ls: illegall option -- %c\n", str[i]);
			printf("usage: ft_ls [-Radglrtu] [file ...]\n");
			exit(1);
		}
		i++;
	}
	tmp = str + 1;
	return (tmp);
}
