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

void	ft_print_dir_name(t_entry *list_start, t_shit *pShit, char *dirname)
{
	if (!(ft_iscinstr(pShit->flags, 'R')))
	{
		if (ft_strcmp(dirname, "./") && (pShit->dirs[1] || pShit->files[0]
										 || pShit->error != 0))
			printf(RESET"%s:\n", dirname);
	}
	else
		if (pShit->subdir != 0 || pShit->dirs[1] || pShit->files[0]
			|| pShit->error != 0)
			printf(RESET"%s:\n", dirname);
	ft_print_column(list_start);
}

void    list_dir_recursive(char *dirname, char *name, t_shit *pShit)
{
    struct dirent *pDirent;
    t_entry *list_start;
	t_entry *list_current;
    DIR *pDir;
    char path[ft_strlen(dirname) + 255];

    pDirent = NULL;
    list_start = NULL;
    ft_strcpy(path, dirname);
    pDir = opendir(dirname);
    if (pDir == NULL)
	{
        if (pShit->subdir != 0 || pShit->dirs[1] || pShit->files[0]
            || pShit->error != 0)
            printf("%s:\n", path);
        printf(RESET"ft_ls: %s: Permission denied\n", name);
        return ;
    }
    if (ft_iscinstr(pShit->flags, 'a') || ft_iscinstr(pShit->flags, 'f'))
        list_start = fill_list_a(pDir, pShit, path, dirname);
    else
        list_start = fill_list(pDir, pShit, path, dirname);
    if (!ft_iscinstr(pShit->flags, 'f'))
	{
        list_start = ft_tri_ascii(list_start, pShit);
		if (ft_iscinstr(pShit->flags, 't'))
		{
			if (ft_iscinstr(pShit->flags, 'u'))
				list_start = ft_tri_access(list_start, pShit);
			else
				list_start = ft_tri_date(list_start, pShit);
		}
	}
    if (ft_iscinstr(pShit->flags, 'l') || ft_iscinstr(pShit->flags, 'g'))
        display_entries_l(list_start, pShit, dirname);
    else
        ft_print_dir_name(list_start, pShit, dirname);
    lstdel(&list_start);
    closedir(pDir);
    if (ft_iscinstr(pShit->flags, 'R'))
    {
        pDir = opendir(dirname);
        list_start = fill_list_rdir(pDir, pShit, path, dirname);
		closedir(pDir);
		if(list_start == NULL)
			return ;
		if (!ft_iscinstr(pShit->flags, 'f'))
			list_start = ft_tri_ascii(list_start, pShit);
		if (ft_iscinstr(pShit->flags, 't'))
		{
			if (ft_iscinstr(pShit->flags, 'u'))
				list_start = ft_tri_access(list_start, pShit);
			else
				list_start = ft_tri_date(list_start, pShit);
		}
		list_current = list_start;
		while(list_current)
		{
			pShit->subdir++;
            printf("\n");
            if (dirname[ft_strlen(dirname) - 1] != '/')
                ft_strcat(path, "/");
            ft_strcat(path, list_current->name);
            list_dir_recursive(path, list_current->name, pShit);
            ft_bzero(path + ft_strlen(dirname),
                     ft_strlen(list_current->name));
			list_current = list_current->next;
		}
		lstdel(&list_start);
	}
}
