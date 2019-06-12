/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:09:09 by jmondino          #+#    #+#             */
/*   Updated: 2019/05/31 18:31:23 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_parseargs(char **av, t_shit *pShit)
{
	int		i;
	int		j;
	int		bool;
	char	*tmp;
	char	*newav[256];

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
		ft_asciiorder(newav);
	ft_fillpShit(tmp, newav, j, pShit);
}

char	**ft_isdir(char **newav, int index, t_shit *pShit)
{
	char	**tab;
	int		i;
	int		j;

	if (newav == NULL)
		return (NULL);
	if (!(tab = malloc(index * sizeof(char *))))
		return (NULL);
	//printf("%ld\n", index * sizeof(char *));
	i = 0;
	j = 0;
	while (newav[i])
	{
		if (ft_strcmp(newav[i],  "--"))
		{
			if (ft_existent(newav[i], 0, pShit))
			{
				tab[j] = ft_strdup(newav[i]);
				j++;
			}
		}
		i++;
	}
	tab[j] = '\0';
	return (tab);
}

char	**ft_isfile(char **newav, int index, t_shit *pShit)
{
	char	**tab;
	int		i;
	int		j;

	if (newav == NULL)
		return (NULL);
	if (!(tab = malloc(index * sizeof(char *))))
		return (NULL);
	i = 0;
	j = 0;
	while (newav[i])
	{
		if (ft_strcmp(newav[i],  "--"))
		{
			if (ft_existent(newav[i], 1, pShit))
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

int		ft_existent(char *str, int here, t_shit *pShit)
{
	DIR				*pDir;
	struct	stat	*pStat;

	if((pStat = malloc(sizeof(struct stat))) == NULL)
        return 0;
	if (here == 1)
	{
		if ((pDir = opendir(str)) == NULL)                        // have to correct this part
		{
			lstat(str, pStat);
			if (!(pStat->st_dev))
			{
				printf ("ft_ls: %s: No such file or directory\n", str);
				pShit->error++;
				return (0);
			}
			return (1);
		}
		return (0);
	}
	if ((pDir = opendir(str)) == NULL)
		return (0);
	return (1);
}

char	*ft_checkflags(char *str)
{
	int		i;
	char	*tmp;

	i = 1;
	while (str[i])
	{
		if (!(OP(str[i])))
		{
			printf("ft_ls: illegall option -- %c\n", str[i]);
			printf("usage: ft_ls [-Ralrt] [file ...]\n");
			exit(1);
		}
		i++;
	}
	tmp = str + 1;
	return (tmp);
}
