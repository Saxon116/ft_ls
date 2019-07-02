/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:30:21 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/02 16:52:21 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	lstdel(t_entry **lst)
{
	t_entry		*curr;
	t_entry		*next;
	int			i;

	curr = *lst;
	while (curr)
	{
		next = curr->next;
		if (curr->has_xattr)
		{
			i = -1;
			while (curr->xattr[++i])
				free(curr->xattr[i]);
			free(curr->xattr);
			free(curr->xattr_sizes);
		}
		free(curr->link_path);
		free(curr->name);
		free(curr->rights);
		free(curr->user);
		free(curr->group);
		free(curr->date_month_modified);
		free(curr->date_time_modified);
		free(curr);
		curr = next;
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
