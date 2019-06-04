/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 14:03:11 by jmondino          #+#    #+#             */
/*   Updated: 2019/06/04 02:58:42 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_display(t_shit *pShit)
{
	int		i;

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
}

void	ft_print_dir_name(t_shit *pShit, char *dirname)
{
	if (!(ft_iscinstr(pShit->flags, 'R')))
	{
		if (ft_strcmp(dirname, "./") && (pShit->dirs[1] || pShit->files[0]))
			printf("%s:\n", dirname);
	}
	else
		if (pShit->subdir != 0 || pShit->dirs[1] || pShit->files[0])
			printf("%s:\n", dirname);
	printf("display normaly\n");
}

void	ft_print_column()
{
	// test git pull pour jmondino
}
