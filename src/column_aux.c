/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 14:05:44 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/03 13:45:47 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_all_names_length(t_entry *lst_st)
{
	int			all_names_length;

	all_names_length = 0;
	while (lst_st)
	{
		all_names_length += ft_strlen(lst_st->name);
		lst_st = lst_st->next;
	}
	return (all_names_length);
}

int		get_list_size(t_entry *lst_st)
{
	int			size;

	size = 0;
	while (lst_st)
	{
		size++;
		lst_st = lst_st->next;
	}
	return (size);
}

void	sort_longest_entries(int n, int *longest_entries)
{
	int			i;
	int			j;
	int			a;

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

char	**array_from_list(t_entry *lst_st)
{
	char		**array;
	int			i;

	i = 0;
	if (!(array = malloc((get_list_size(lst_st) + 1) * sizeof(char*))))
		return (NULL);
	while (lst_st)
	{
		array[i] = ft_strdup(lst_st->name);
		i++;
		lst_st = lst_st->next;
	}
	array[i] = NULL;
	return (array);
}

void	print_row(t_entry *lst_st, int ijpercol, char **array, int col_wid_j)
{
	t_entry		*browse;
	int			length;

	browse = lst_st;
	length = 0;
	while (array[length])
		length++;
	if (ijpercol < length && array[ijpercol])
	{
		while (ft_strcmp(browse->name, array[ijpercol]))
			browse = browse->next;
		print_color(array[ijpercol], browse->type, browse->rights);
		print_spaces(col_wid_j - ft_strlen(array[ijpercol]));
		browse = lst_st;
	}
}
