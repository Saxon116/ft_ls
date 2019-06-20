/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 18:23:54 by jmondino          #+#    #+#             */
/*   Updated: 2019/06/20 15:15:08 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_return(t_shit *pShit)
{
    if (!ft_iscinstr(pShit->flags, 'l'))
        printf("\n");
    if (pShit->dirs[0])
        printf("\n");
}

void    print_color_l(char *entry, int type, char *rights)
{
    printf(RESET);
    if (S_ISDIR(type))
        printf(BOLDCYAN"%s", entry);
    if (S_ISREG(type))
    {
        if (ft_iscinstr(rights, 'x'))
            printf(RED"%s", entry);
        else
            printf(RESET"%s", entry);
    }
    if (S_ISLNK(type))
        printf(MAGENTA"%s", entry);
    if (S_ISBLK(type))
        printf(BLUEBLUE"%s", entry);
    if (S_ISCHR(type))
        printf(YELLOWBLUE"%s", entry);
    if (S_ISSOCK(type))
        printf(GREEN"%s", entry);
    if (S_ISFIFO(type))
		printf(BOLDCYANGREEN"%s", entry);
    printf(RESET);
}

void    print_color(char *entry, int type, char *rights)
{
	printf(RESET);
    if (S_ISDIR(type))
        printf(BOLDCYAN"%s  ", entry);
    if (S_ISREG(type))
    {
        if (ft_iscinstr(rights, 'x'))
            printf(RED"%s  ", entry);
        else
            printf(RESET"%s  ", entry);
    }
    if (S_ISLNK(type))
        printf(MAGENTA"%s  ", entry);
    if (S_ISBLK(type))
        printf(BLUEBLUE"%s  ", entry);
    if (S_ISCHR(type))
        printf(YELLOWBLUE"%s  ", entry);
    if (S_ISSOCK(type))
        printf(GREEN"%s  ", entry);
    if (S_ISFIFO(type))
		printf(BOLDCYANGREEN"%s  ", entry);
    printf(RESET);
}

void    print_normally(t_entry *list_start)
{
    t_entry     *browse;

    browse = list_start;
    while (browse)
    {
        print_color(browse->name, browse->type, browse->rights);
        browse = browse->next;
    }
    if (list_start)
        printf("\n");
}

