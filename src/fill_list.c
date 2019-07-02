/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 12:15:22 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/02 14:31:46 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_entry     *fill_list_d(t_args *pargs)
{
    t_entry         *start;
    t_entry         *browse;
    int             i;

    i = -1;
    browse = NULL;
    start = browse;
    if (pargs->dsfs[0])
    {
        while (pargs->dsfs[++i])
        {
            if (!browse)
            {
                browse = add_new_entry(pargs->dsfs[i], pargs->dsfs[i], pargs);
                start = browse;
            }
            else
            {
                browse->next = add_new_entry(pargs->dsfs[i], pargs->dsfs[i],
											 pargs);
                browse = browse->next;
            }
        }
    }
    else
    {
        browse = add_new_entry(".", ".", pargs);
        start = browse;
    }
    return (start);
}

t_entry     *fill_list_rdir(DIR *pdir, t_args *pargs, char *path, char *dirname)
{
    t_entry *list_start;
    t_entry *list_curr;
    struct dirent *pdirent;

    list_curr = NULL;
    list_start = NULL;
    while ((pdirent = readdir(pdir)) != NULL)
    {
        if (pdirent->d_type == DT_DIR)
        {
            if((!ft_iscinstr(pargs->flags, 'a') && pdirent->d_name[0] != '.') ||
			   (ft_iscinstr(pargs->flags, 'a') && check_dir_a(pdirent->d_name)))
            {
                if (dirname[ft_strlen(dirname) - 1] != '/')
                    ft_strcat(path, "/");
                ft_strcat(path, pdirent->d_name);
                if (!list_curr)
                {
                    list_curr = add_new_entry(path, pdirent->d_name, pargs);
                    list_start = list_curr;
                }
                else
                {
                    list_curr->next = add_new_entry(path, pdirent->d_name, pargs);
                    list_curr = list_curr->next;
                }
                ft_bzero(path + ft_strlen(dirname), ft_strlen(pdirent->d_name));
            }
        }
    }
    return list_start;
}

t_entry     *fill_list(DIR *pdir, t_args *pargs, char *path, char *dirname)
{
    t_entry         *list_start;
    t_entry         *list_curr;
    struct dirent   *pdirent;

    list_curr = NULL;
    list_start = NULL;
    while ((pdirent = readdir(pdir)) != NULL)
    {
        if (pdirent->d_name[0] != '.')
        {
            if (path[ft_strlen(path) - 1] != '/')
                ft_strcat(path, "/");
            ft_strcat(path, pdirent->d_name);
            if (!list_curr)
            {
                list_curr = add_new_entry(path, pdirent->d_name, pargs);
                list_start = list_curr;
            }
            else
            {
                list_curr->next = add_new_entry(path, pdirent->d_name, pargs);
                list_curr = list_curr->next;
            }
            ft_bzero(path + ft_strlen(dirname), ft_strlen(pdirent->d_name));
        }
    }
    return (list_start);
}

t_entry     *fill_list_a(DIR *pdir, t_args *pargs, char *path, char *dirname)
{
    t_entry         *list_start;
    t_entry         *list_curr;
    struct dirent   *pdirent;

    list_curr = NULL;
    list_start = NULL;
    while ((pdirent = readdir(pdir)) != NULL)
    {
        if (dirname[ft_strlen(dirname) - 1] != '/')
            ft_strcat(path, "/");
        ft_strcat(path, pdirent->d_name);
        if (!list_curr)
        {
            list_curr = add_new_entry(path, pdirent->d_name, pargs);
            list_start = list_curr;
        }
        else
        {
            list_curr->next = add_new_entry(path, pdirent->d_name, pargs);
            list_curr = list_curr->next;
        }
        ft_bzero(path + ft_strlen(dirname), ft_strlen(pdirent->d_name));
    }
    return (list_start);
}

int check_dir_a(char *name)
{
    if(ft_strcmp(name, ".") == 0 || ft_strcmp(name, "..") == 0)
        return (0);
    return (1);
}
