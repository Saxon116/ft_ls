/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 18:23:54 by jmondino          #+#    #+#             */
/*   Updated: 2019/06/19 18:25:52 by jmondino         ###   ########.fr       */
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
    if (type == DT_DIR)
        printf(BOLDCYAN"%s", entry);
    if (type == DT_REG)
    {
        if (ft_iscinstr(rights, 'x'))
            printf(RED"%s", entry);
        else
            printf(RESET"%s", entry);
    }
    if (type == DT_LNK)
        printf(MAGENTA"%s", entry);
    if (type == DT_BLK)
        printf(BLUEBLUE"%s", entry);
    if (type == DT_CHR)
        printf(YELLOWBLUE"%s", entry);
    if (type == DT_SOCK)
        printf(GREEN"%s", entry);
    //if (type == DT_FIFO)
    //printf(BOLDCYANGREEN"%s", entry);
    printf(RESET);
}

void    print_color(char *entry, int type, char *rights)
{
    printf(RESET);
    if (type == DT_DIR)
        printf(BOLDCYAN"%s  ", entry);
    if (type == DT_REG)
    {
        if (ft_iscinstr(rights, 'x'))
            printf(RED"%s  ", entry);
        else
            printf(RESET"%s  ", entry);
    }
    if (type == DT_LNK)
        printf(MAGENTA"%s  ", entry);
    if (type == DT_BLK)
        printf(BLUEBLUE"%s  ", entry);
    if (type == DT_CHR)
        printf(YELLOWBLUE"%s  ", entry);
    if (type == DT_SOCK)
        printf(GREEN"%s  ", entry);
    //if (type == DT_FIFO)
    //printf(BOLDCYANGREEN"%s", entry);
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

