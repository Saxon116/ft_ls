/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:09:09 by jmondino          #+#    #+#             */
/*   Updated: 2019/05/23 16:58:07 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_parseoption(char *av)
{
	int		i;

	i = 1;
	if (!(ft_strcmp(av, "--")))
		return (0);
	while (av[i])
	{
		if (!(OP(av[i])))
		{
			printf("ft_ls: illegall option -- %c\n", av[i]);
			printf("usage: ft_ls [-Ralrt] [file ...]\n");
			exit(1);
		}
		i++;
	}
	return (1);
}

int		checkoption(char *option, char c)
{
	int		i;

	if (option == NULL)
		return (0);
	i = 0;
	while (option[i])
	{
		if (option[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_revtab(char **tab)
{
	int		i;
	int		j;
	char	*tmp;

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
