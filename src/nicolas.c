/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nicolas.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:35:01 by jmondino          #+#    #+#             */
/*   Updated: 2019/06/26 18:16:32 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void get_basic_offsets(int	**offsets, t_entry *list_current)
{
	if (num_length(list_current->hard_links) > offsets[0][0])
		offsets[0][0] = num_length(list_current->hard_links);
	if (num_length(list_current->size) > offsets[0][1])
		offsets[0][1] = num_length(list_current->size);
	if (num_length(list_current->date_day_modified) > offsets[0][2])
		offsets[0][2] = num_length(list_current->date_day_modified);
	if (ft_strlen(list_current->user) > (unsigned) offsets[0][3])
		offsets[0][3] = ft_strlen(list_current->user);
	if (ft_strlen(list_current->group) > (unsigned) offsets[0][4])
		offsets[0][4] = ft_strlen(list_current->group);
}

void get_special_offsets(int **offsets, t_entry *list_current)
{
	if (S_ISBLK(list_current->type) || S_ISCHR(list_current->type))
	{
		if (num_length(list_current->major) > offsets[0][5])
			offsets[0][5] = num_length(list_current->major);
		if (num_length(list_current->minor) > offsets[0][6])
			offsets[0][6] = num_length(list_current->minor);
		if (num_length(list_current->minor) + num_length(list_current->major) >
			offsets[0][7])
			offsets[0][7] = num_length(list_current->minor) + num_length(list_current->major);
	}
}
int     *get_offsets(t_entry *list_start)
{
    int         *offsets;
    t_entry     *list_current;

    if ((offsets = malloc(sizeof(int) * 8)) == NULL)
        return 0;
    offsets[0] = 0;
    offsets[1] = 0;
    offsets[2] = 0;
    offsets[3] = 0;
    offsets[4] = 0;
    offsets[5] = 0;
    offsets[6] = 0;
    offsets[7] = 0;
    list_current = list_start;
    while (list_current)
    {
        get_basic_offsets(&offsets, list_current);
        get_special_offsets(&offsets, list_current);
        list_current = list_current->next;
    }
    return (offsets);
}

void display_first_entries(t_entry *list_current, t_shit *pShit, int *offsets)
{
	print_type(list_current);
	printf("%s", list_current->rights);
	if(list_current->has_xattr > 0)
		printf("@ ");
	else if(list_current->has_acl)
		printf("+ ");
	else
		printf("  ");
	print_spaces(offsets[0] - (num_length(list_current->hard_links)));
	printf("%d", list_current->hard_links);
	if (!ft_iscinstr(pShit->flags, 'g'))
	{
		printf(" %s ", list_current->user);
		print_spaces(offsets[3] - (ft_strlen(list_current->user)));
	}
	printf(" %s  ", list_current->group);
	print_spaces(offsets[4] - (ft_strlen(list_current->group)));
	print_spaces(offsets[1] - (num_length(list_current->size)));
}

void display_last_entries(t_entry *list_current, int *offsets)
{
	if (S_ISBLK(list_current->type) || S_ISCHR(list_current->type))
	{
		print_spaces(offsets[5] - num_length(list_current->major));
		printf("%d, ", list_current->major);
		print_spaces(offsets[6] - num_length(list_current->minor));
		printf("%d ", list_current->minor);
	}
	else
	{
		print_spaces(offsets[7] + 2);
		printf("%d ", list_current->size);
	}
	printf("%s", list_current->date_month_modified);
	print_spaces(offsets[2] - (num_length(list_current->date_day_modified)));
	printf(" %d", list_current->date_day_modified);
	if(ft_strlen(list_current->date_time_modified) == 4)
		print_spaces(1);
	printf(" %s ",list_current->date_time_modified);
	print_color_l(list_current->name, list_current->type, list_current->rights);
	if (S_ISLNK(list_current->type))
		printf(" -> %s", list_current->link_path);
}

void display_extended_attr(t_entry *list_current, t_shit *pShit)
{
	if(list_current->has_xattr > 0 && ft_iscinstr(pShit->flags, '@'))
	{
		int i = 0;
		printf("\n");
		while(list_current->xattr[i])
		{
			printf("        %s", list_current->xattr[i]);
			print_spaces(28 - ft_strlen(list_current->xattr[i]) - num_length(list_current->xattr_sizes[i]));
			printf("%d\n", list_current->xattr_sizes[i]);
			i++;
		}
	}
	else
		printf("\n");
}


void    display_entries_l(t_entry *list_start, t_shit *pShit, char *dirname)
{
    t_entry     *list_current;
    int         *offsets;

    ft_total(list_start, pShit, dirname);
    offsets = get_offsets(list_start);
    list_current = list_start;
    while (list_current)
    {
		display_first_entries(list_current, pShit, offsets);
		display_last_entries(list_current, offsets);
		display_extended_attr(list_current, pShit);
        list_current = list_current->next;
    }
    free(offsets);
}

void sort_longest_entries(int n, int *longest_entries)
{
	int i;
	int j;
	int a;

	i = 0;
	j = 0;
	a = 0;
    while (i < n)
    {
        j = i + 1;
        while (j < n)
        {
            if (longest_entries[i] < longest_entries[j])
            {
                a = longest_entries[i];
                longest_entries[i] = longest_entries[j];
                longest_entries[j] = a;
            }
            j++;
        }
        i++;
    }
}

int     num_of_columns(t_entry *list_start, int terminal_width)
{
    int longest_entries[get_list_size(list_start)];
    t_entry *list_current;
    int i;
	int n;
    int spaces;

    list_current = list_start;
    n = get_list_size(list_start);
    spaces = 0;
	i = 0;
    while (list_current)
    {
        longest_entries[i] = ft_strlen(list_current->name);
        list_current = list_current->next;
        i++;
    }
    sort_longest_entries(n, longest_entries);
    i = 0;
    spaces += longest_entries[i] + 2;
    while (spaces < terminal_width)
    {
        i++;
		spaces += longest_entries[i] + 2;
    }
    return (i == 0 ? 1 : i);
}

void print_row_entries(t_entry *list_start, int ijpercol, char **str_array, int column_widths_j)
{
	t_entry *browse;
	int length;

    browse = list_start;
	length = 0;
	while (str_array[length])
        length++;
	if (ijpercol < length
		&& str_array[ijpercol])
	{
		while (ft_strcmp(browse->name, str_array[ijpercol]))
			browse = browse->next;
		print_color(str_array[ijpercol], browse->type, browse->rights);
		print_spaces(column_widths_j - ft_strlen(str_array[ijpercol]));
		browse = list_start;
	}
}

void print_rows(char **str_array, int *column_widths, int columns, t_entry *list_start\
	)
{
    int i;
    int j;
    int per_column;

    i = 0;
    j = 0;
    per_column = get_list_size(list_start) / columns + 1;
    while (i < per_column)
    {
        j = 0;
        while (j < columns)
        {
            print_row_entries(list_start, i + (j * (per_column)),
			str_array, column_widths[j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

int get_all_names_length(t_entry *list_start)
{
	int all_names_length;

	all_names_length = 0;
	while (list_start)
    {
        all_names_length += ft_strlen(list_start->name);
        list_start = list_start->next;
    }
	return (all_names_length);
}

void free_columns(char **str_array)
{
	int columns;

	columns = 0;
    while (str_array[columns])
    {
        free(str_array[columns]);
        columns++;
    }
    free(str_array);
}

void    ft_print_column(t_entry *list_start)
{
    unsigned int all_names_length;
    unsigned int list_size;
    unsigned int terminal_width;
    int columns;
    int *column_widths;
    char **str_array;
    struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    terminal_width = w.ws_col;
    all_names_length = get_all_names_length(list_start);
    list_size = get_list_size(list_start);
    columns = num_of_columns(list_start, terminal_width);
    str_array = array_from_list(list_start);
    if (all_names_length + list_size * 2  > terminal_width)
    {
        column_widths = get_column_widths(str_array, columns, list_size);
        print_rows(str_array, column_widths, columns, list_start);
        free(column_widths);
    }
    else
        print_normally(list_start);
	free_columns(str_array);
}

t_entry     *add_new_entry(char *path, char *entry_name, t_shit *pShit)
{
    t_entry *entry;
    struct stat pstat;
    char  l[1024];
	int ut_flags;

	ut_flags = (ft_iscinstr(pShit->flags, 't') && ft_iscinstr(pShit->flags, 'u'));
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
    if (S_ISBLK(entry->type) || S_ISCHR(entry->type))
    {
        entry->minor = minor(pstat.st_rdev);
        entry->major = major(pstat.st_rdev);
    }
    entry->link_path = get_link_path(path);
    entry->name = ft_strdup(entry_name);
    entry->rights = permissions(pstat.st_mode);
    entry->hard_links = pstat.st_nlink;
    entry->size = pstat.st_size;
    entry->user = ft_strdup(getpwuid(pstat.st_uid) == NULL ? "" : getpwuid(pstat.st_uid)->pw_name);
    entry->group = ft_strdup(getgrgid(pstat.st_gid) == NULL ? "" : getgrgid(pstat.st_gid)->gr_name);
    entry->date_day_modified = get_day(ctime(ut_flags ? &pstat.st_atimespec.tv_sec : &pstat.st_mtimespec.tv_sec));
    entry->block_size = pstat.st_blocks;
    entry->date_month_modified =
		ft_strsub(ctime(ut_flags ? &pstat.st_atimespec.tv_sec : &pstat.st_mtimespec.tv_sec), 4, 3);
    entry->mtime = pstat.st_mtime;
    entry->date_time_modified = (time(0) - pstat.st_mtime) > SIXMONTHS ?
		ft_strsub(ctime(ut_flags ? &pstat.st_atimespec.tv_sec : &pstat.st_mtimespec.tv_sec), 20, 4) :
        ft_strsub(ctime(ut_flags ? &pstat.st_atimespec.tv_sec : &pstat.st_mtimespec.tv_sec), 11, 5);
    entry->date_accessed = pstat.st_atimespec.tv_sec;
    entry->next = NULL;
    return (entry);
}

void    list_dir_recursive(char *dirname, char *name, t_shit *pShit)
{
    struct dirent *pDirent;
    t_entry *list_start;
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
