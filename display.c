/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 14:03:11 by jmondino          #+#    #+#             */
/*   Updated: 2019/06/19 16:59:11 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_display(t_shit *pShit)
{
	int		i;
	t_entry	*files_lst;

	i = 0;
	while (pShit->files[i])
    {
		if (ft_iscinstr(pShit->flags, 'l'))
		{
			files_lst = add_new_entry2(pShit->files[i]);
			display_entries_l(files_lst, pShit, pShit->files[i]);
		}
		else
			printf("%s ", pShit->files[i]);
        i++;
    }
    if (i != 0)
    {
		if (!ft_iscinstr(pShit->flags, 'l'))
			printf("\n");
        if (pShit->dirs[0])
            printf("\n");
    }
    i = 0;
    while (pShit->dirs[i])
    {
        list_dir_recursive(pShit->dirs[i], pShit->dirs[i], pShit);
        i++;
        if (pShit->dirs[i])
            printf("\n");
    }
}

void	print_color_l(char *entry, int type, char *rights)
{
	printf(RESET);
	if (type == DT_DIR)
		printf(BOLDCYAN"%s", entry);
	if (type == DT_REG)
	{
		if (ft_iscinstr(rights, 'x'))
			printf(GREEN"%s", entry);
		else
			printf(RESET"%s", entry);
	}
	if (type == DT_LNK)
		printf(MAGENTA"%s", entry);
	if (type == DT_UNKNOW)
		printf("%s", entry);
	if (type == DT_FIFO)
		printf("")
	printf(RESET);
}

void	print_color(char *entry, int type, char *rights)
{
	printf(RESET);
	if (type == DT_DIR)
		printf(BOLDCYAN"%s  ", entry);
	if (type == DT_REG)
	{
		if (ft_iscinstr(rights, 'x'))
			printf(GREEN"%s  ", entry);
		else
			printf(RESET"%s  ", entry);
	}
	if (type == DT_LNK)
		printf(MAGENTA"%s  ", entry);
	printf(RESET);
}

void print_normally(t_entry *list_start)
{
	t_entry		*browse;

	browse = list_start;
	while (browse)
	{
		print_color(browse->name, browse->type, browse->rights);
		browse = browse->next;
	}
	if (list_start)
		printf("\n");
}

int get_list_size(t_entry *list_start)
{
	int size;

	size = 0;
	while (list_start)
	{
		size++;
		list_start = list_start->next;
	}
	return (size);
}

int get_longest_name(t_entry *list_start)
{
	unsigned int longest_name;

	longest_name = 0;
	while (list_start)
	{
		if( ft_strlen(list_start->name) > longest_name)
			longest_name = ft_strlen(list_start->name);
		list_start = list_start->next;
	}
	return (longest_name);
}

int num_of_columns(t_entry *list_start, int terminal_width)
{
	int longest_entries[get_list_size(list_start)];
	t_entry *list_current;
	int i, j, n, a;
	int spaces;

	list_current = list_start;
	i = 0;
	j = 0;
	a = 0;
	n = get_list_size(list_start);
	spaces = 0;
	while(list_current)
	{
		longest_entries[i] = ft_strlen(list_current->name);
		list_current = list_current->next;
		i++;
	}
	i = 0;
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
	i = 0;
	spaces += longest_entries[i] + 2;
	while(spaces < terminal_width)
	{
		i++;
		spaces += longest_entries[i] + 2;
	}
	return (i == 0 ? 1 : i);
}

char **array_from_list(t_entry *list_start)
{
	char **array;
	int i;

	i = 0;
	if((array = malloc((get_list_size(list_start) + 1) * sizeof(char*))) == NULL)
		return 0;
	while(list_start)
	{
		array[i] = ft_strdup(list_start->name);
		i++;
		list_start = list_start->next;
	}
	array[i] = NULL;
	return (array);
}

int longest_in_column(char **str_array, int start, int end, int list_size)
{
	int i;
	unsigned int longest_name;

	longest_name = 0;
	i = start;
	while (i < list_size && str_array[i] && i < end)
	{
		if (ft_strlen(str_array[i]) > longest_name)
			longest_name = ft_strlen(str_array[i]);
		i++;
	}
	return (longest_name);
}

int *get_column_widths(char **str_array, int num_of_columns, int list_size)
{
	int *column_widths;
	int per_column;
	int i;

	per_column = list_size / (num_of_columns == 0 ? 1 : num_of_columns) + 1;
	i = 0;
	if ((column_widths = malloc(sizeof(int) * list_size)) == NULL)
		return 0;
	while (i < num_of_columns)
	{
		column_widths[i] = longest_in_column(str_array,
			 i * per_column, i * per_column + per_column, list_size);
		i++;
	}
	return (column_widths);
}

void print_rows(char **str_array, int *column_widths, int columns, t_entry *list_start)
{
	int i;
	int j;
	int length;
	int per_column;
	t_entry *browse;

	browse = list_start;
	i = 0;
	j = 0;
	length = 0;
	per_column = get_list_size(list_start) / columns + 1;
	while (str_array[length])
		length++;
	while (i < per_column)
	{
		j = 0;
		while (j < columns)
		{
			if (i + (j * (per_column)) < length
			&& str_array[i + (j * (per_column))])
			{
				while (ft_strcmp(browse->name, str_array[i + (j * (per_column))]))
					browse = browse->next;
				print_color(str_array[i + (j * (per_column))], browse->type, browse->rights);
				print_spaces(column_widths[j] -
				ft_strlen(str_array[i + (j * (per_column))]));
				browse = list_start;
			}
			j++;
		}
		printf("\n");
		i++;
	}
}


void	ft_print_column(t_entry *list_start)
{
	unsigned int all_names_length;
	unsigned int list_size;
	unsigned int terminal_width;
	int columns;
	char **str_array;
	t_entry *list_current;
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	terminal_width = w.ws_col;
	all_names_length = 0;
	list_size = get_list_size(list_start);
	columns = num_of_columns(list_start, terminal_width);
	list_current = list_start;
	str_array = array_from_list(list_start);
	while (list_current)
	{
		all_names_length += ft_strlen(list_current->name);
		list_current = list_current->next;
	}
	if (all_names_length + list_size * 2  > terminal_width)
	{
		int *column_widths = get_column_widths(str_array,
		columns, list_size);
		print_rows(str_array, column_widths, columns, list_start);
		free(column_widths);
	}
	else
		print_normally(list_start);
	int i = 0;
	while (str_array[i])
	{
		free(str_array[i]);
		i++;
	}
	free(str_array);
}

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
