/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:49:13 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/02 16:34:40 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_print_column(t_entry *lst_st)
{
	unsigned int	all_names_length;
	unsigned int	list_size;
	unsigned int	terminal_width;
	int				col;
	int				*wds;
	char			**array;
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	terminal_width = w.ws_col;
	all_names_length = get_all_names_length(lst_st);
	list_size = get_list_size(lst_st);
	col = num_columns(lst_st, terminal_width);
	array = array_from_list(lst_st);
	if (all_names_length + list_size * 2 > terminal_width)
	{
		wds = get_column_widths(array, col, list_size);
		print_rows(array, wds, col, lst_st);
		free(wds);
	}
	else
		print(lst_st);
	free_columns(array);
}

int			*get_column_widths(char **array, int num_columns, int list_size)
{
	int				*wds;
	int				per_column;
	int				i;

	per_column = list_size / (num_columns == 0 ? 1 : num_columns) + 1;
	i = 0;
	if ((wds = malloc(sizeof(int) * list_size)) == NULL)
		return (0);
	while (i < num_columns)
	{
		wds[i] = longest_in_column(array, i * per_column,
										i * per_column + per_column, list_size);
		i++;
	}
	return (wds);
}

int			longest_in_column(char **array, int start, int end, int list_size)
{
	int				i;
	unsigned int	longest_name;

	longest_name = 0;
	i = start;
	while (i < list_size && array[i] && i < end)
	{
		if (ft_strlen(array[i]) > longest_name)
			longest_name = ft_strlen(array[i]);
		i++;
	}
	return (longest_name);
}

int			num_columns(t_entry *lst_st, int terminal_width)
{
	int				longest_entries[get_list_size(lst_st)];
	t_entry			*list_curr;
	int				i;
	int				n;
	int				spaces;

	list_curr = lst_st;
	n = get_list_size(lst_st);
	spaces = 0;
	i = 0;
	while (list_curr)
	{
		longest_entries[i] = ft_strlen(list_curr->name);
		list_curr = list_curr->next;
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

void		print_rows(char **array, int *wds, int col, t_entry *lst_st)
{
	int				i;
	int				j;
	int				per_column;

	i = 0;
	j = 0;
	per_column = get_list_size(lst_st) / col + 1;
	while (i < per_column)
	{
		j = 0;
		while (j < col)
		{
			print_row(lst_st, i + (j * (per_column)),
							array, wds[j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
