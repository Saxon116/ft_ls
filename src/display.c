/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 14:03:11 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/01 10:56:13 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void					ft_display(t_shit *pShit)
{
	int					i;
	t_entry				*files_lst;

	i = -1;
	if (ft_iscinstr(pShit->flags, 'l') || ft_iscinstr(pShit->flags, 'g'))
	{
		while (pShit->files[++i])
		{
			files_lst = add_new_entry(pShit->files[i], pShit->files[i], pShit);
			display_entries_l(files_lst, pShit, pShit->files[i]);
		}
	}
	else
		display(pShit, i);
	if (pShit->files[0] && pShit->dirs[0])
		printf("\n");
	i = 0;
	while (pShit->dirs[i])
	{
		list_dir_recursive(pShit->dirs[i], pShit->dirs[i], pShit);
		i++;
		if (pShit->dirs[i])
			printf("\n");
	}
}

int 				get_list_size(t_entry *list_start)
{
	int				size;

	size = 0;
	while (list_start)
	{
		size++;
		list_start = list_start->next;
	}
	return (size);
}

int					get_longest_name(t_entry *list_start)
{
	unsigned int	longest_name;

	longest_name = 0;
	while (list_start)
	{
		if (ft_strlen(list_start->name) > longest_name)
			longest_name = ft_strlen(list_start->name);
		list_start = list_start->next;
	}
	return (longest_name);
}

char 				**array_from_list(t_entry *list_start)
{
	char			**array;
	int 			i;

	i = 0;
	if((array = malloc((get_list_size(list_start) + 1) * sizeof(char*))) == NULL)
		return (0);
	while (list_start)
	{
		array[i] = ft_strdup(list_start->name);
		i++;
		list_start = list_start->next;
	}
	array[i] = NULL;
	return (array);
}

void			ft_print_dir_name(t_entry *list_start, t_shit *pShit, char *dirname)
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
