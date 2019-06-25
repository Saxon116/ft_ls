/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 18:23:54 by jmondino          #+#    #+#             */
/*   Updated: 2019/06/25 11:29:35 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void    display(t_shit *pShit, int i)
{
    t_entry *start;
	t_entry *browse;

    browse = NULL;
    start = browse;
	while (pShit->files[++i])
	{
		if (!browse)
		{
			browse = add_new_entry(pShit->files[i], pShit->files[i]);
			start = browse;
		}
        else
		{
			browse->next = add_new_entry(pShit->files[i], pShit->files[i]);
			browse = browse->next;
		}
    }
	if (start)
		ft_print_column(start);
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

