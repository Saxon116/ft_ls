/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:10:14 by nkellum           #+#    #+#             */
/*   Updated: 2019/05/29 18:13:39 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void list_dir(DIR *pDir)
{
	struct dirent *pDirent;

	while ((pDirent = readdir(pDir)) != NULL)
	{
		if(pDirent->d_name[0] != '.')
			printf("%s ", pDirent->d_name);
	}
	printf("\n");
	closedir(pDir);
}

int get_day(char *date)
{
	int i;

	i = 0;
	while(!ft_isdigit(date[i]))
		i++;
	return (ft_atoi(date + i));
}

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


 t_entry *add_new_entry(char *path, char *entry_name, int is_folder)
{
	t_entry	*entry;
	struct stat	*pstat;

	if((pstat = malloc(sizeof(struct stat))) == NULL)
		return 0;
	if((entry = malloc(sizeof(t_entry))) == NULL)
		return 0;
	stat(path, pstat);
	entry->is_folder = is_folder;
	entry->name = ft_strdup(entry_name);
	entry->rights = permissions(pstat->st_mode);
	entry->hard_links = pstat->st_nlink;
	entry->size = pstat->st_size;
	entry->user = ft_strdup(getpwuid(pstat->st_uid)->pw_name);
	entry->group = ft_strdup(getgrgid(pstat->st_gid)->gr_name);
	entry->date_day_modified = get_day(ctime(&pstat->st_mtimespec.tv_sec));
	entry->date_month_modified =
	ft_strsub(ctime(&pstat->st_mtimespec.tv_sec), 3, 4);
	entry->date_time_modified =
	ft_strsub(ctime(&pstat->st_mtimespec.tv_sec), 11, 5);
	entry->date_accessed = pstat->st_mtimespec.tv_sec;
	entry->next = NULL;
	return entry;
}

int list_dir_recursive(char *dirname)
{
	struct dirent	*pDirent;

 	t_entry	*list_start;
	t_entry	*list_current;
	DIR *pDir;
	char path[ft_strlen(dirname) + 255]; // 255 more chars for subdirectory path

	list_current = NULL;
	ft_strcpy(path, dirname); // set path to the current directory path
	pDir = opendir(dirname);
	if (pDir == NULL)
	{
	    	printf("Cannot open %s directory: %s\n", dirname, strerror(errno));
	    	return 1;
	}
	printf("%s:\n", dirname);
	while ((pDirent = readdir(pDir)) != NULL)
	{
		if(pDirent->d_name[0] != '.')
		{ // ignore hidden entries
			//printf("%s ", pDirent->d_name); // list entries normally
		if(dirname[ft_strlen(dirname) - 1] != '/')
			ft_strcat(path, "/");
		ft_strcat(path, pDirent->d_name);
		if(!list_current)
		{
			list_current = add_new_entry(path, pDirent->d_name,
				pDirent->d_type == DT_DIR);
			list_start = list_current;
		}
		else
		{
			list_current->next = add_new_entry(path, pDirent->d_name,
				pDirent->d_type == DT_DIR);
			list_current = list_current->next;
		}
		//printf("user is %s ", add_new_entry(path, pDirent->d_name)->user);
		ft_bzero(path + ft_strlen(dirname),
		ft_strlen(pDirent->d_name) +
		dirname[ft_strlen(dirname) - 1] != '/');
	}
	}
	list_current = list_start;
	while(list_current)
	{
		printf("%c%s %d %s %s %d %s %d %s %s\n",
		list_current->is_folder ? 'd' : '-', list_current->rights,
		list_current->hard_links, list_current->user, list_current->group,
		list_current->size, list_current->date_month_modified,
		list_current->date_day_modified, list_current->date_time_modified,
		list_current->name);
		list_current = list_current->next;
	}
	printf("\n");
	closedir(pDir);
	pDir = opendir(dirname); // resetting pDir to first file entry for new loop

	while ((pDirent = readdir(pDir)) != NULL)
	{
		if(pDirent->d_name[0] != '.')
		{
			if(pDirent->d_type == DT_DIR) // if entry is a directory
			{
				printf("\n");
				if(dirname[ft_strlen(dirname) - 1] != '/')
					ft_strcat(path, "/");
				ft_strcat(path, pDirent->d_name); // add subdirectory name to full path
				list_dir_recursive(path); // list contents of subdirectory
				ft_bzero(path + ft_strlen(dirname),
				ft_strlen(pDirent->d_name) +
				dirname[ft_strlen(dirname) - 1] != '/'); // reset path for next subdirectory
			}
		}
	}
	closedir(pDir);
	return 0;
}


int main (int argc, char **argv)
{
	list_dir_recursive((argc < 2) ? "." : argv[1]);
        return 0;
}
