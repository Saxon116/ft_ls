/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:10:14 by nkellum           #+#    #+#             */
/*   Updated: 2019/05/23 17:21:10 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_shit		*initstru(int ac,char **av)
{
	t_shit		*pShit;

	if ((pShit = malloc(sizeof(t_shit))) == NULL)
		return (NULL);
	pShit->option = NULL;
	pShit->ac = ac;
	pShit->av = av;
	return pShit;
}

int main (int ac, char **av)
{
  	struct dirent 	*pDirent;
   	DIR 			*pDir;
	t_shit			*pShit;

	if (!(pShit = initstru(ac, av)))
		return (0);
	pShit->index = 0;
	if (av[1] && av[1][0] == '-')
	{
		if (ft_parseoption(av[1]))
			pShit->option = ft_strdup(av[1] + 1);
		pShit->index++;
	}
	if (ac == 1 || (pShit->option && ac == 2))
		ft_pathless(pDir, pDirent, pShit);
	else
		ft_manypaths(pDir, pDirent, pShit);
	return (0);
}
