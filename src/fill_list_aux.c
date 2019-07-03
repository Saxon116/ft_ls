/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 11:39:30 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/03 15:22:28 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_entry		*fill_it(t_args *pargs)
{
	t_entry		*start;
	t_entry		*browse;
	int			i;

	i = -1;
	browse = NULL;
	while (pargs->dsfs[++i])
	{
		if (!browse)
		{
			browse = add_new_entry(pargs->dsfs[i], pargs->dsfs[i], pargs);
			start = browse;
		}
		else
		{
			browse->next = add_new_entry(pargs->dsfs[i], pargs->dsfs[i],
										pargs);
			browse = browse->next;
		}
	}
	return (start);
}
