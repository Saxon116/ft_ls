/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:10:14 by nkellum           #+#    #+#             */
/*   Updated: 2019/06/20 18:01:43 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_pShit(t_shit *pShit)
{
	int i = 0;
	free(pShit->flags);
	i = 0;
	while (pShit->files[i])
	{
		free(pShit->files[i]);
		i++;
	}
	free(pShit->files);
	i = 0;
	while(pShit->dirs[i])
	{
		free(pShit->dirs[i]);
		i++;
	}
	free(pShit->dirs);
}



int 	main(int ac, char **av)
{
	t_shit		*pShit;

	(void)ac;
	if (!(pShit = initstru()))
		return (0);
	ft_parseargs(av, pShit);
	ft_display(pShit);
	free_pShit(pShit);
	free(pShit);
	return (0);
}
