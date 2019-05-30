/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:10:14 by nkellum           #+#    #+#             */
/*   Updated: 2019/05/30 18:28:40 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int 	main(int ac, char **av)
{
	t_shit			*pShit;
	int				i;

	(void)ac;
	if (!(pShit = initstru()))
		return (0);
	ft_parseargs(av, pShit);
	i = 0;
	while (pShit->files[i])
	{
		printf("%s ", pShit->files[i]);
		i++;
	}
	if (i != 0)
	{
		printf("\n");
		if (pShit->dirs[0])
			printf("\n");
	}
	i = 0;
	while (pShit->dirs[i])
	{
		list_dir_recursive(pShit->dirs[i], pShit);
		i++;
		if (pShit->dirs[i])
			printf("\n");
	}
	return (0);
}
