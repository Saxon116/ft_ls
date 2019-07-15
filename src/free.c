/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:30:21 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/15 17:57:40 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_data(t_entry *entry)
{
	free(entry->link_path);
	free(entry->name);
	free(entry->rights);
	free(entry->user);
	free(entry->group);
	free(entry->date_month_modified);
	free(entry->date_time_modified);
}

void	lstdel(t_entry **lst)
{
	t_entry		*curr;
	t_entry		*temp;
	int			i;

	curr = *lst;
	while (curr)
	{
		temp = curr->next;
		if (curr->has_xattr)
		{
			i = -1;
			while (curr->xattr[++i])
				free(curr->xattr[i]);
			free(curr->xattr);
			free(curr->xattr_sizes);
		}
		free_data(curr);
		free(curr);
		curr = temp;
	}
	*lst = NULL;
}

void	free_columns(char **array)
{
	int		col;

	col = 0;
	while (array[col])
	{
		free(array[col]);
		col++;
	}
	free(array);
}

void	free_pargs(t_args *pargs)
{
	int		i;

	free(pargs->flags);
	i = -1;
	while (pargs->files[++i])
		free(pargs->files[i]);
	free(pargs->files);
	i = -1;
	while (pargs->dirs[++i])
		free(pargs->dirs[i]);
	free(pargs->dirs);
	i = -1;
	while (pargs->newav[++i])
		free(pargs->newav[i]);
	free(pargs->newav);
	i = -1;
	while (pargs->dsfs[++i])
		free(pargs->dsfs[i]);
	free(pargs->dsfs);
}
