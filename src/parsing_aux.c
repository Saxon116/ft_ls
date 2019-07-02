/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 10:39:52 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/02 14:27:26 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_checkflags(char *str)
{
	int		i;
	char	*tmp;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'a' && str[i] != 'r' && str[i] != 'l' && str[i] != 'R'
			&& str[i] != 't' && str[i] != 'u' && str[i] != '@' && str[i] != 'g'
			&& str[i] != 'd' && str[i] != 'f')
		{
			printf("ft_ls: illegall option -- %c\n", str[i]);
			printf("usage: ft_ls [-Radfglrtu] [file ...]\n");
			exit(1);
		}
		i++;
	}
	tmp = str + 1;
	return (tmp);
}

int		fill_newav(char **av, t_args *pargs, char **tmp, int j)
{
	int		i;
	int		bool;

	bool = 0;
	i = 0;
	while (av[++i])
	{
		if (!(ft_strcmp(av[i],  "--")) || av[i][0] != '-')
			bool = 1;
		if ((av[i][0] == '-' && av[i][1]) && bool == 0)
			*tmp = ft_strjoin(*tmp, ft_checkflags(av[i]));
		else
		{
			if (ft_strcmp(av[i], "--"))
				pargs->newav[j++] = ft_strdup(av[i]);
		}
	}
	pargs->newav[j] = NULL;
	return (j);
}

void    ft_fillpargs(char *flags, char **newav, int index, t_args *pargs)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    pargs->flags = flags;
    pargs->files = ft_isfile(newav, index, pargs);
    pargs->dirs = ft_isdir(newav, index);
    if (newav[0] == NULL)
    {
        free(pargs->dirs);
        if (!(pargs->dirs = (char **)malloc(sizeof(char *) * 2)))
            return ;
        pargs->dirs[0] = ft_strdup(".");
        pargs->dirs[1] = NULL;
    }
    if (ft_iscinstr(pargs->flags, 'r'))
    {
        ft_revtab(pargs->files);
        ft_revtab(pargs->dirs);
    }
    while (pargs->files[i])
        pargs->dsfs[j++] = ft_strdup(pargs->files[i++]);
    i = 0;
    while (pargs->dirs[i])
        pargs->dsfs[j++] = ft_strdup(pargs->dirs[i++]);
    pargs->dsfs[j] = NULL;
}

t_args      *initstru(char **av)
{
    t_args      *pargs;
    int         i;

    i = 1;
    if ((pargs = malloc(sizeof(t_args))) == NULL)
        return (NULL);
    while (av[i])
        i++;
    if (!(pargs->dsfs = (char **)malloc(sizeof(char *) * i + 1)))
        pargs->dsfs = NULL;
    pargs->flags = NULL;
    pargs->files = NULL;
    pargs->dirs = NULL;
    if (!(pargs->newav = (char **)malloc(sizeof(char *) * i + 1)))
        pargs->newav = NULL;
    pargs->subdir = 0;
    pargs->error = 0;
    return (pargs);
}
