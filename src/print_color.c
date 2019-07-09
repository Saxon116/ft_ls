/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:33:12 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/09 16:14:40 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print(t_entry *lst_st)
{
	t_entry		*browse;

	browse = lst_st;
	while (browse)
	{
		print_color(browse->name, browse->type, browse->rights);
		browse = browse->next;
	}
	if (lst_st)
		ft_printf("\n");
}

void	print_color_l(char *entry, int type, char *rights)
{
	ft_printf(RESET);
	if (S_ISDIR(type))
		ft_printf(BOLDCYAN"%s", entry);
	if (S_ISREG(type))
	{
		if (ft_iscinstr(rights, 'x'))
			ft_printf(RED"%s", entry);
		else
			ft_printf(RESET"%s", entry);
	}
	if (S_ISLNK(type))
		ft_printf(MAGENTA"%s", entry);
	if (S_ISBLK(type))
		ft_printf(BLUEBLUE"%s", entry);
	if (S_ISCHR(type))
		ft_printf(YELLOWBLUE"%s", entry);
	if (S_ISSOCK(type))
		ft_printf(GREEN"%s", entry);
	if (S_ISFIFO(type))
		ft_printf(BOLDCYANGREEN"%s", entry);
	ft_printf(RESET);
}

void	print_color(char *entry, int type, char *rights)
{
	ft_printf(RESET);
	if (S_ISDIR(type))
		ft_printf(BOLDCYAN"%s  ", entry);
	if (S_ISREG(type))
	{
		if (ft_iscinstr(rights, 'x'))
			ft_printf(RED"%s  ", entry);
		else
			ft_printf(RESET"%s  ", entry);
	}
	if (S_ISLNK(type))
		ft_printf(MAGENTA"%s  ", entry);
	if (S_ISBLK(type))
		ft_printf(BLUEBLUE"%s  ", entry);
	if (S_ISCHR(type))
		ft_printf(YELLOWBLUE"%s\033[0m  ", entry);
	if (S_ISSOCK(type))
		ft_printf(GREEN"%s  ", entry);
	if (S_ISFIFO(type))
		ft_printf(BOLDCYANGREEN"%s\033[0m  ", entry);
	ft_printf(RESET);
}
