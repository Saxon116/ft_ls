/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:25:46 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/02 13:26:20 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void    ft_total(t_entry *list_start, t_args *pargs, char *dirname)
{
    struct stat     pstat;
    t_entry         *browse;
    int             total;
    int             i;

    lstat(dirname, &pstat);
    total = 0;
    i = 0;
    browse = list_start;
    if ((pargs->error != 0 || pargs->subdir != 0 || pargs->dirs[1]
		 || pargs->files[0]) && (!S_ISREG(pstat.st_mode))
        && !ft_iscinstr(pargs->flags, 'd'))
        printf("%s:\n", dirname);
    while (browse)
    {
        total += browse->block_size;
        browse = browse->next;
        i++;
    }
    if (i != 0 && (!S_ISREG(pstat.st_mode)) && !ft_iscinstr(pargs->flags, 'd'))
        printf("total %d\n", total);
}
