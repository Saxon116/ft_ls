/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:10:14 by nkellum           #+#    #+#             */
/*   Updated: 2019/05/30 17:10:06 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int 	main(int ac, char **av)
{
  	struct dirent 	*pDirent;
   	DIR 			*pDir;
	t_shit			*pShit;
	int				i;

	if (!(pShit = initstru(ac, av)))
		return (0);
	ft_parseargs(av, pShit);
	/*if (pShit->files[0])
	  ft_affiles(pShit);*/
	i = 0;
	while (pShit->dirs[i])
	{
		list_dir_recursive(pShit->dirs[i]);
		i++;
	}
	return (0);
}
