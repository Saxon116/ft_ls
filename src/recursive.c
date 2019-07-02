/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:36:34 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/02 15:37:35 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_dir_name(t_entry *lst_st, t_args *pargs, char *dirname)
{
	if (!(ft_iscinstr(pargs->flags, 'R')))
	{
		if (ft_strcmp(dirname, "./") && (pargs->dirs[1] || pargs->files[0]
										 || pargs->error != 0))
			printf(RESET"%s:\n", dirname);
	}
	else
		if (pargs->subdir != 0 || pargs->dirs[1] || pargs->files[0]
			|| pargs->error != 0)
			printf(RESET"%s:\n", dirname);
	ft_print_column(lst_st);
}

void    list_dir_recursive(char *dirname, char *name, t_args *pargs)
{
    struct dirent *pdirent;
    t_entry *lst_st;
	t_entry *list_current;
    DIR *pdir;
    char path[ft_strlen(dirname) + 255];

    pdirent = NULL;
    lst_st = NULL;
    ft_strcpy(path, dirname);
    pdir = opendir(dirname);
    if (pdir == NULL)
	{
        if (pargs->subdir != 0 || pargs->dirs[1] || pargs->files[0]
            || pargs->error != 0)
            printf("%s:\n", path);
        printf(RESET"ft_ls: %s: Permission denied\n", name);
        return ;
    }
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
    closedir(pdir);
    if (ft_iscinstr(pargs->flags, 'R'))
    {
        pdir = opendir(dirname);
        lst_st = fill_list_rdir(pdir, pargs, path, dirname);
		closedir(pdir);
		if(lst_st == NULL)
			return ;
		if (!ft_iscinstr(pargs->flags, 'f'))
			lst_st = ft_tri_ascii(lst_st, pargs);
		if (ft_iscinstr(pargs->flags, 't'))
		{
			if (ft_iscinstr(pargs->flags, 'u'))
				lst_st = ft_tri_access(lst_st, pargs);
			else
				lst_st = ft_tri_date(lst_st, pargs);
		}
		list_current = lst_st;
		while(list_current)
		{
			pargs->subdir++;
            printf("\n");
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
}
