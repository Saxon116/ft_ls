/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:10:14 by nkellum           #+#    #+#             */
/*   Updated: 2019/06/25 11:43:36 by jmondino         ###   ########.fr       */
/*   Updated: 2019/06/20 19:54:09 by nkellum          ###   ########.fr       */
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
		if(current->has_xattr)
		{
			int i = 0;
			while(current->xattr[i])
			{
				free(current->xattr[i]);
				i++;
			}
			free(current->xattr);
			free(current->xattr_sizes);
		}
		free(current->link_path);
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
	char 		*buf;
	ssize_t 	len;

	if ((buf = malloc(1024)) == NULL)
		return 0;
	len = readlink(path, buf, 1023);
	if (len != -1)
	{
  		buf[len] = '\0';
		return buf;
	}
	else
	{
		free(buf);
		return ft_strdup("");
	}
}

t_entry 	*add_new_entry2(char *entry_name)
{
	t_entry			*entry;
	struct stat		pstat;

	if ((entry = malloc(sizeof(t_entry))) == NULL)
		return 0;
	lstat(entry_name, &pstat);
	entry->type = pstat.st_mode;
	entry->link_path = get_link_path(entry_name);
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
	entry->mtime = pstat.st_mtime;
	entry->next = NULL;
	return (entry);
}

int get_xattr_num(char *attributes, int size)
{
	int i;
	int num;
	int reset;

	reset = 0;
	num = 0;
	i = 0;
	while(i < size)
	{
		if(attributes[i] == '\0')
			num++;
		i++;
	}
	return (num);
}

char **get_xattr_list(char *attributes, int size)
{
	char **array;
	int i;
	int j;
	int num_of_xattr;

	i = 0;
	j = 0;
	num_of_xattr = get_xattr_num(attributes, size);
	if((array = malloc((num_of_xattr + 1) * sizeof(char*))) == NULL)
		return 0;
	while(i < num_of_xattr)
	{
		array[i] = ft_strdup(attributes + j);
		while((attributes[j]) != '\0')
			j++;
		j++;
		i++;
	}
	array[i] = NULL;
	return (array);
}

int *get_xattr_sizes(char **attributes, char *path, int length)
{
	int 		*sizes;
	int			i;

	i = 0;
	if ((sizes = malloc(sizeof(int) * length)) == NULL)
		return 0;
	while(i < length)
	{
		sizes[i] = getxattr(path, attributes[i], NULL, 0, 0, XATTR_NOFOLLOW);
		i++;
	}
	return (sizes);

}

int has_acl(char *path)
{
	acl_t acl = NULL;
    acl_entry_t dummy;

    acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
    if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1) {
        acl_free(acl);
        acl = NULL;
    }
    if (acl != NULL)
	{
		acl_free(acl);
        return (1);
	}
    else
	{
		acl_free(acl);
        return (0);
	}
}

t_entry 	*add_new_entry(char *path, char *entry_name)
{
	t_entry	*entry;
	struct stat	pstat;
	char  l[1024];

	if ((entry = malloc(sizeof(t_entry))) == NULL)
		return 0;
	if (lstat(path, &pstat) == -1)
		printf("Error\n");
	entry->has_xattr = listxattr(path, l, 1024,  XATTR_NOFOLLOW);
	if(entry->has_xattr)
	{
		entry->xattr = get_xattr_list(l, entry->has_xattr);
		entry->xattr_sizes = get_xattr_sizes(entry->xattr, path, get_xattr_num(l, entry->has_xattr));
	}
	entry->has_acl = has_acl(path);
	entry->type = pstat.st_mode;
	entry->link_path = get_link_path(path);
	entry->name = ft_strdup(entry_name);
	entry->rights = permissions(pstat.st_mode);
	entry->hard_links = pstat.st_nlink;
	entry->size = pstat.st_size;
	entry->user = ft_strdup(getpwuid(pstat.st_uid) == NULL ? "" : getpwuid(pstat.st_uid)->pw_name);
	entry->group = ft_strdup(getgrgid(pstat.st_gid) == NULL ? "" : getgrgid(pstat.st_gid)->gr_name);
	entry->date_day_modified = get_day(ctime(&pstat.st_mtimespec.tv_sec));
	entry->block_size = pstat.st_blocks;
	entry->date_month_modified =
	ft_strsub(ctime(&pstat.st_ctimespec.tv_sec), 4, 3);
	entry->date_time_modified =
	ft_strsub(ctime(&pstat.st_ctimespec.tv_sec), 11, 5);
	entry->date_accessed = pstat.st_atimespec.tv_sec;
	entry->mtime = pstat.st_mtime;
	entry->next = NULL;
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
			if (path[ft_strlen(path) - 1] != '/')
				ft_strcat(path, "/");
			ft_strcat(path, pDirent->d_name);
			if (!list_current)
			{
				list_current = add_new_entry(path, pDirent->d_name);
				list_start = list_current;
			}
			else
			{
				list_current->next = add_new_entry(path, pDirent->d_name);
				list_current = list_current->next;
			}
			ft_bzero(path + ft_strlen(dirname), ft_strlen(pDirent->d_name));
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
			list_current = add_new_entry(path, pDirent->d_name);
			list_start = list_current;
		}
		else
		{
			list_current->next = add_new_entry(path, pDirent->d_name);
			list_current = list_current->next;
		}
		ft_bzero(path + ft_strlen(dirname),	ft_strlen(pDirent->d_name));
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
	fresh = list;
	return (fresh);
}


void	ft_rev_list(t_entry **list)
{
	t_entry		*current;
	t_entry		*prev;
	t_entry		*next;

	current = *list;
	prev = NULL;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*list = prev;
}

void	list_dir_recursive(char *dirname, char *name, t_shit *pShit)
{
	struct dirent *pDirent;
	t_entry	*list_start;
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
	if (ft_iscinstr(pShit->flags, 'a'))
		list_start = fill_list_a(pDir, pDirent, path, dirname);
	else
		list_start = fill_list(pDir, pDirent, path, dirname);
	list_start = ft_tri_ascii(list_start, pShit);
	if (ft_iscinstr(pShit->flags, 't'))
	{
		if (ft_iscinstr(pShit->flags, 'u'))
			list_start = ft_tri_access(list_start, pShit);
		else
			list_start = ft_tri_date(list_start, pShit);
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
		while ((pDirent = readdir(pDir)) != NULL)
		{
			if (pDirent->d_name[0] != '.')
			{
				if (pDirent->d_type == DT_DIR)
				{
					pShit->subdir++;
					printf("\n");
					if (dirname[ft_strlen(dirname) - 1] != '/')
						ft_strcat(path, "/");
					ft_strcat(path, pDirent->d_name);
					list_dir_recursive(path, pDirent->d_name, pShit);
					ft_bzero(path + ft_strlen(dirname),
							 ft_strlen(pDirent->d_name) +
							 dirname[ft_strlen(dirname) - 1] != '/');
				}
			}
		}
	closedir(pDir);
	}
}
