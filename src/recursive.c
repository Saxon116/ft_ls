/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:36:34 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/15 14:15:09 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_dir_name(t_entry *lst_st, t_args *pargs, char *dirname)
{
	if (!(ft_iscinstr(pargs->flags, 'R')))
	{
		if ((pargs->dirs[1] || pargs->files[0]
			|| pargs->error != 0))
			ft_printf(RESET"%s:\n", dirname);
	}
	else
	{
		if (pargs->subdir != 0 || pargs->dirs[1] || pargs->files[0]
			|| pargs->error != 0)
			ft_printf(RESET"%s:\n", dirname);
	}
	ft_print_column(lst_st);
}

void	get_and_display_entries(DIR *pdir, t_args *pargs,
	char *path, char *dirname)
{
	t_entry			*lst_st;

	lst_st = NULL;
	if (ft_iscinstr(pargs->flags, 'a') || ft_iscinstr(pargs->flags, 'f'))
		lst_st = fill_list_a(pdir, pargs, path, dirname);
	else
		lst_st = fill_list(pdir, pargs, path, dirname);
	if (!ft_iscinstr(pargs->flags, 'f'))
	{
		lst_st = ft_tri_ascii(lst_st, pargs);
		if (ft_iscinstr(pargs->flags, 't'))
		{
			if (ft_iscinstr(pargs->flags, 'u'))
				lst_st = ft_tri_access(lst_st, pargs);
			else
				lst_st = ft_tri_date(lst_st, pargs);
		}
	}
	if (ft_iscinstr(pargs->flags, 'l') || ft_iscinstr(pargs->flags, 'g'))
		display_entries_l(lst_st, pargs, dirname);
	else
		ft_print_dir_name(lst_st, pargs, dirname);
	lstdel(&lst_st);
}

t_entry	*sort_list_r(t_entry *lst_st, t_args *pargs)
{
	if (!ft_iscinstr(pargs->flags, 'f'))
		lst_st = ft_tri_ascii(lst_st, pargs);
	if (ft_iscinstr(pargs->flags, 't'))
	{
		if (ft_iscinstr(pargs->flags, 'u'))
			lst_st = ft_tri_access(lst_st, pargs);
		else
			lst_st = ft_tri_date(lst_st, pargs);
	}
	return (lst_st);
}

void	cycle_subdirs(t_args *pargs,
	char *path, char *dirname)
{
	t_entry			*lst_st;
	t_entry			*list_current;
	DIR				*pdir;

	pdir = opendir(dirname);
	lst_st = fill_list_rdir(pdir, pargs, path, dirname);
	closedir(pdir);
	if (lst_st == NULL)
		return ;
	list_current = sort_list_r(lst_st, pargs);
	while (list_current)
	{
		pargs->subdir++;
		ft_printf("\n");
		if (dirname[ft_strlen(dirname) - 1] != '/')
			ft_strcat(path, "/");
		ft_strcat(path, list_current->name);
		list_dir_recursive(path, list_current->name, pargs);
		ft_bzero(path + ft_strlen(dirname),
				ft_strlen(list_current->name));
		list_current = list_current->next;
	}
	lstdel(&lst_st);
}

void	list_dir_recursive(char *dirname, char *name, t_args *pargs)
{
	struct dirent	*pdirent;
	DIR				*pdir;
	char			path[ft_strlen(dirname) + 255];

	pdirent = NULL;
	ft_strcpy(path, dirname);
	pdir = opendir(dirname);
	if (pdir == NULL)
		return (p_denied(pargs, path, name));
	get_and_display_entries(pdir, pargs, path, dirname);
	closedir(pdir);
	if (ft_iscinstr(pargs->flags, 'R'))
		cycle_subdirs(pargs, path, dirname);
}
