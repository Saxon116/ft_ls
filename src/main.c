/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 10:31:36 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/02 13:29:10 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_args		*pargs;

	(void)ac;
	if (!(pargs = initstru(av)))
		return (0);
	ft_parseargs(av, pargs);
	if (ft_iscinstr(pargs->flags, 'd'))
		ft_display_d(pargs);
	else
		ft_display(pargs);
	free_pargs(pargs);
	free(pargs);
	return (0);
}
