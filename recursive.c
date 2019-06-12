/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:10:14 by nkellum           #+#    #+#             */
/*   Updated: 2019/06/04 03:39:52 by nkellum          ###   ########.fr       */
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
	struct stat	*pstat;

	if((pstat = malloc(sizeof(struct stat))) == NULL)
		return 0;
	if((entry = malloc(sizeof(t_entry))) == NULL)
		return 0;
	lstat(path, pstat);
	entry->type = type;
	entry->link_path = get_link_path(path);
	entry->name = ft_strdup(entry_name);
	entry->rights = permissions(pstat->st_mode);
	entry->hard_links = pstat->st_nlink;
	entry->size = pstat->st_size;
	entry->user = ft_strdup(getpwuid(pstat->st_uid)->pw_name);
	entry->group = ft_strdup(getgrgid(pstat->st_gid)->gr_name);
	entry->date_day_modified = get_day(ctime(&pstat->st_mtim.tv_sec));
	entry->block_size = pstat->st_blocks;
	entry->date_month_modified =
	ft_strsub(ctime(&pstat->st_mtim.tv_sec), 4, 3);
	entry->date_time_modified =
	ft_strsub(ctime(&pstat->st_mtim.tv_sec), 11, 5);
	entry->date_accessed = pstat->st_mtim.tv_sec;
	entry->next = NULL;
	free(pstat);
	return entry;
}

t_entry 	*fill_list(DIR *pDir, struct dirent *pDirent, char *path, char *dirname)
{
	t_entry	*list_start;
	t_entry	*list_current;

	list_current = NULL;
	list_start = NULL;
	while ((pDirent = readdir(pDir)) != NULL)
	{
		if(pDirent->d_name[0] != '.') // ignore hidden entries
		{
			if(dirname[ft_strlen(dirname) - 1] != '/')
				ft_strcat(path, "/");

			ft_strcat(path, pDirent->d_name);


			if(!list_current)
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
		if(dirname[ft_strlen(dirname) - 1] != '/')
			ft_strcat(path, "/");
		ft_strcat(path, pDirent->d_name);
		if(!list_current)
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
