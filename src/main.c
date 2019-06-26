/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:10:14 by nkellum           #+#    #+#             */
/*   Updated: 2019/06/26 13:16:30 by jmondino         ###   ########.fr       */
/*   Updated: 2019/06/20 18:01:43 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_pShit(t_shit *pShit)
{
	int 	i;
	free(pShit->flags);
	i = -1;
	while (pShit->files[++i])
		free(pShit->files[i]);
	free(pShit->files);
	i = -1;
	while(pShit->dirs[++i])
		free(pShit->dirs[i]);
	free(pShit->dirs);
	i = -1;
	while (pShit->newav[++i])
		free(pShit->newav[i]);
	free(pShit->newav);
	i = -1;
	while (pShit->dsfs[++i])
		free(pShit->dsfs[i]);
	free(pShit->dsfs);
}

int 	main(int ac, char **av)
{
	t_shit		*pShit;

	(void)ac;
	if (!(pShit = initstru(av)))
		return (0);
	ft_parseargs(av, pShit);
	if (ft_iscinstr(pShit->flags, 'd'))
		ft_display_d(pShit);
	else
		ft_display(pShit);
	free_pShit(pShit);
	free(pShit);
	return (0);
}
