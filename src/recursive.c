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

void	ft_print_dir_name(t_entry *list_start, t_args *pargs, char *dirname)
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
	ft_print_column(list_start);
}

void    list_dir_recursive(char *dirname, char *name, t_args *pargs)
{
    struct dirent *pdirent;
    t_entry *list_start;
	t_entry *list_current;
    DIR *pdir;
    char path[ft_strlen(dirname) + 255];

    pdirent = NULL;
    list_start = NULL;
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
        list_start = fill_list_a(pdir, pargs, path, dirname);
    else
        list_start = fill_list(pdir, pargs, path, dirname);
    if (!ft_iscinstr(pargs->flags, 'f'))
	{
        list_start = ft_tri_ascii(list_start, pargs);
		if (ft_iscinstr(pargs->flags, 't'))
		{
			if (ft_iscinstr(pargs->flags, 'u'))
				list_start = ft_tri_access(list_start, pargs);
			else
				list_start = ft_tri_date(list_start, pargs);
		}
	}
    if (ft_iscinstr(pargs->flags, 'l') || ft_iscinstr(pargs->flags, 'g'))
        display_entries_l(list_start, pargs, dirname);
    else
        ft_print_dir_name(list_start, pargs, dirname);
    lstdel(&list_start);
    closedir(pdir);
    if (ft_iscinstr(pargs->flags, 'R'))
    {
        pdir = opendir(dirname);
        list_start = fill_list_rdir(pdir, pargs, path, dirname);
		closedir(pdir);
		if(list_start == NULL)
			return ;
		if (!ft_iscinstr(pargs->flags, 'f'))
			list_start = ft_tri_ascii(list_start, pargs);
		if (ft_iscinstr(pargs->flags, 't'))
		{
			if (ft_iscinstr(pargs->flags, 'u'))
				list_start = ft_tri_access(list_start, pargs);
			else
				list_start = ft_tri_date(list_start, pargs);
		}
		list_current = list_start;
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
		lstdel(&list_start);
	}
}
