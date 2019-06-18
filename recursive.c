/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:10:14 by nkellum           #+#    #+#             */
/*   Updated: 2019/06/18 15:01:02 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char *permissions(mode_t perm)
{
    char *modeval;

	if((modeval = malloc(sizeof(char) * 9 + 1)) == NULL)
		return 0;
    modeval[0] = (perm & S_IRUSR) ? 'r' : '-';
    modeval[1] = (perm & S_IWUSR) ? 'w' : '-';
    modeval[2] = (perm & S_IXUSR) ? 'x' : '-';
    modeval[3] = (perm & S_IRGRP) ? 'r' : '-';
    modeval[4] = (perm & S_IWGRP) ? 'w' : '-';
    modeval[5] = (perm & S_IXGRP) ? 'x' : '-';
    modeval[6] = (perm & S_IROTH) ? 'r' : '-';
    modeval[7] = (perm & S_IWOTH) ? 'w' : '-';
    modeval[8] = (perm & S_IXOTH) ? 'x' : '-';
    modeval[9] = '\0';
    return modeval;
}

void	lstdel(t_entry **lst)
{
	t_entry *current;
	t_entry *next;

	current = *lst;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->rights);
		free(current->user);
		free(current->group);
		free(current->date_month_modified);
		free(current->date_time_modified);
		free(current);
		current = next;
	}
	*lst = NULL;
}

char *get_link_path(char *path)
{
	char *buf;

	if((buf = malloc(1024)) == NULL)
		return 0;
	ssize_t len = readlink(path, buf, 1023);
	if(len != -1)
	{
  		buf[len] = '\0';
		return buf;
	}
	else
		return ft_strdup("");
}

t_entry 	*add_new_entry(char *path, char *entry_name, int type)
{
	t_entry	*entry;
	struct stat	pstat;

	if ((entry = malloc(sizeof(t_entry))) == NULL)
		return 0;
	lstat(path, &pstat);
	entry->type = type;
	entry->link_path = get_link_path(path);
	entry->name = ft_strdup(entry_name);
	entry->rights = permissions(pstat.st_mode);
	entry->hard_links = pstat.st_nlink;
	entry->size = pstat.st_size;
	entry->user = ft_strdup(getpwuid(pstat.st_uid)->pw_name);
	entry->group = ft_strdup(getgrgid(pstat.st_gid)->gr_name);
	entry->date_day_modified = get_day(ctime(&pstat.st_mtimespec.tv_sec));
	entry->block_size = pstat.st_blocks;
	entry->date_month_modified =
	ft_strsub(ctime(&pstat.st_mtimespec.tv_sec), 4, 3);
	entry->date_time_modified =
	ft_strsub(ctime(&pstat.st_mtimespec.tv_sec), 11, 5);
	entry->date_accessed = pstat.st_mtimespec.tv_sec;
	entry->next = NULL;
	entry->mtime = pstat.st_mtime;
	return (entry);
}

t_entry 	*fill_list(DIR *pDir, struct dirent *pDirent, char *path, char *dirname)
{
	t_entry	*list_start;
	t_entry	*list_current;

	list_current = NULL;
	list_start = NULL;
	while ((pDirent = readdir(pDir)) != NULL)
	{
		if (pDirent->d_name[0] != '.')
		{
			if (dirname[ft_strlen(dirname) - 1] != '/')
				ft_strcat(path, "/");
			ft_strcat(path, pDirent->d_name);
			if (!list_current)
			{
				list_current = add_new_entry(path, pDirent->d_name,
											 pDirent->d_type);
				list_start = list_current;
			}
			else
			{
				list_current->next = add_new_entry(path, pDirent->d_name,
												   pDirent->d_type);
				list_current = list_current->next;
			}
			ft_bzero(path + ft_strlen(dirname),
					 ft_strlen(pDirent->d_name) +
					 dirname[ft_strlen(dirname) - 1] != '/');
		}
	}
	return list_start;
}


t_entry 	*fill_list_a(DIR *pDir, struct dirent *pDirent, char *path, char *dirname)
{
	t_entry	*list_start;
	t_entry	*list_current;

	list_current = NULL;
	list_start = NULL;
	while ((pDirent = readdir(pDir)) != NULL)
	{
		if (dirname[ft_strlen(dirname) - 1] != '/')
			ft_strcat(path, "/");
		ft_strcat(path, pDirent->d_name);
		if (!list_current)
		{
			list_current = add_new_entry(path, pDirent->d_name,
										 pDirent->d_type);
			list_start = list_current;
		}
		else
		{
			list_current->next = add_new_entry(path, pDirent->d_name,
											   pDirent->d_type);
			list_current = list_current->next;
		}
		ft_bzero(path + ft_strlen(dirname),
				 ft_strlen(pDirent->d_name) +
				 dirname[ft_strlen(dirname) - 1] != '/');
	}
	return list_start;
}

t_entry		*ft_tri_ascii(t_entry *list, t_shit *pShit)
{
	t_entry *start;
	t_entry *lstart;
	t_entry *fresh;
	int		swap;

	if (list == NULL)
		return NULL;
	start = list;
	fresh = start;
	swap = 1;
	lstart = NULL;
	while (swap)
	{
		swap = 0;
		start = list;
		while (start->next != lstart)
		{
			if ((ft_strcmp(start->name, start->next->name)) > 0)
			{
				ft_swap(start, start->next);
				swap = 1;
			}
			start = start->next;
		}
		lstart = start;
	}
	if (ft_iscinstr(pShit->flags, 'r'))
		ft_rev_list(&list);
	return (fresh);
}

t_entry		*ft_tri_date(t_entry *list, t_shit *pShit)
{
	t_entry *start;
	t_entry *lstart;
	t_entry *fresh;
	int		swap;

	if (list == NULL)
		return NULL;
	start = list;
	fresh = start;
	swap = 1;
	lstart = NULL;
	while (swap)
	{
		swap = 0;
		start = list;
		while (start->next != lstart)
		{
			if (start->mtime < start->next->mtime)
			{
				ft_swap(start, start->next);
				swap = 1;
			}
			start = start->next;
		}
		lstart = start;
	}
	if (ft_iscinstr(pShit->flags, 'r'))
		ft_rev_list(&list);
	return fresh;
}

void	ft_rev_list(t_entry **list)
{
	t_entry		*current;
	t_entry		*start;
	t_entry		*next;

	current = *list;
	start = NULL;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = start;
		start = current;
		current = next;
	}
	*list = start;
}

void	ft_swap(t_entry *a, t_entry *b)
{
	t_entry		*tmp;

	tmp = fill_tmp();
	ft_fill(tmp, a);
	ft_fill(a, b);
	ft_fill(b, tmp);
	free(tmp);
}

t_entry		*fill_tmp(void)
{
	t_entry		*tmp;

	if (!(tmp = malloc(sizeof(t_entry))))
		return NULL;
	tmp->type = 0;
	tmp->name = NULL;
	tmp->rights = NULL;
	tmp->hard_links = 0;
	tmp->user = NULL;
	tmp->group = NULL;
	tmp->size = 0;
	tmp->block_size = 0;
	tmp->date_month_modified = NULL;
	tmp->date_day_modified = 0;
	tmp->date_time_modified = NULL;
	tmp->date_accessed = 0;
	tmp->link_path = NULL;
	tmp->next = NULL;
	tmp->mtime = 0;
	return (tmp);
}

void	ft_fill(t_entry *fill, t_entry *src)
{
	fill->type = src->type;
	fill->name = src->name;
	fill->rights = src->rights;
	fill->hard_links = src->hard_links;
	fill->user = src->user;
	fill->group = src->group;
	fill->size = src->size;
	fill->block_size = src->block_size;
	fill->date_month_modified = src->date_month_modified;
	fill->date_day_modified = src->date_day_modified;
	fill->date_time_modified = src->date_time_modified;
	fill->date_accessed = src->date_accessed;
	fill->link_path = src->link_path;
	fill->mtime = src->mtime;
}

void	list_dir_recursive(char *dirname, t_shit *pShit)
{
	struct dirent *pDirent;
	t_entry	*list_start;
	DIR *pDir;
	char path[ft_strlen(dirname) + 255]; // 255 more chars for subdirectory path

	pDirent = NULL;
	list_start = NULL;
	ft_strcpy(path, dirname); // set path to the current directory path
	pDir = opendir(dirname);
	if(pDir == NULL)
		return ;
	if (ft_iscinstr(pShit->flags, 'a'))
		list_start = fill_list_a(pDir, pDirent, path, dirname);
	else
		list_start = fill_list(pDir, pDirent, path, dirname);
	list_start = ft_tri_ascii(list_start, pShit);
	if (ft_iscinstr(pShit->flags, 't'))
		list_start = ft_tri_date(list_start, pShit);
	if (ft_iscinstr(pShit->flags, 'l'))
		display_entries_l(list_start, pShit, dirname);
	else
		ft_print_dir_name(list_start, pShit, dirname);
	lstdel(&list_start);
	closedir(pDir);
	if (ft_iscinstr(pShit->flags, 'R'))
	{
		pDir = opendir(dirname); // resetting pDir to first file entry for new loop
		while ((pDirent = readdir(pDir)) != NULL)
		{
			if (pDirent->d_name[0] != '.')
			{
				if (pDirent->d_type == DT_DIR) // if entry is a directory
				{
					pShit->subdir++;
					printf("\n");
					if (dirname[ft_strlen(dirname) - 1] != '/')
						ft_strcat(path, "/");
					ft_strcat(path, pDirent->d_name); // add subdirectory name to full path

					list_dir_recursive(path, pShit); // list contents of subdirectory
					ft_bzero(path + ft_strlen(dirname),
							 ft_strlen(pDirent->d_name) +
							 dirname[ft_strlen(dirname) - 1] != '/'); // reset path for next subdirectory
				}
			}
		}
	closedir(pDir);
	}
}
