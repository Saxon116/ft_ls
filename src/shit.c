/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:51:04 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/02 12:15:03 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void    ft_fillpargs(char *flags, char **newav, int index, t_args *pargs)
{
	int		i;
	int		j;

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
	int			i;

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

int 	get_day(char *date)
{
    int i;

    i = 0;
	if (date)
	{
		while (!ft_isdigit(date[i]))
			i++;
		return (ft_atoi(date + i));
	}
	return 0;
}
