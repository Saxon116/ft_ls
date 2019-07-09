/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:25:09 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/09 16:14:47 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_entries_l(t_entry *lst_st, t_args *pargs, char *dirname)
{
	t_entry		*list_curr;
	int			*offsets;

	ft_total(lst_st, pargs, dirname);
	offsets = get_offsets(lst_st);
	list_curr = lst_st;
	while (list_curr)
	{
		display_first_entries(list_curr, pargs, offsets);
		display_last_entries(list_curr, offsets);
		display_extended_attr(list_curr, pargs);
		list_curr = list_curr->next;
	}
	free(offsets);
}

void	display_first_entries(t_entry *list_curr, t_args *pargs, int *offsets)
{
	print_type(list_curr);
	ft_printf("%s", list_curr->rights);
	if (list_curr->has_xattr > 0)
		ft_printf("@ ");
	else if (list_curr->has_acl)
		ft_printf("+ ");
	else
		ft_printf("  ");
	print_spaces(offsets[0] - (num_length(list_curr->hard_links)));
	ft_printf("%d", list_curr->hard_links);
	if (!ft_iscinstr(pargs->flags, 'g'))
	{
		ft_printf(" %s ", list_curr->user);
		print_spaces(offsets[3] - (ft_strlen(list_curr->user)));
	}
	ft_printf(" %s  ", list_curr->group);
	print_spaces(offsets[4] - (ft_strlen(list_curr->group)));
	print_spaces(offsets[1] - (num_length(list_curr->size)));
}

void	display_last_entries(t_entry *list_curr, int *offsets)
{
	if (S_ISBLK(list_curr->type) || S_ISCHR(list_curr->type))
	{
		print_spaces(offsets[5] - num_length(list_curr->major));
		ft_printf("%d, ", list_curr->major);
		print_spaces(offsets[6] - num_length(list_curr->minor));
		ft_printf("%d ", list_curr->minor);
	}
	else
	{
		print_spaces(offsets[7] + 2);
		ft_printf("%d ", list_curr->size);
	}
	ft_printf("%s", list_curr->date_month_modified);
	print_spaces(offsets[2] - (num_length(list_curr->date_day_modified)));
	ft_printf(" %d", list_curr->date_day_modified);
	if (ft_strlen(list_curr->date_time_modified) == 4)
		print_spaces(1);
	ft_printf(" %s ", list_curr->date_time_modified);
	print_color_l(list_curr->name, list_curr->type, list_curr->rights);
	if (S_ISLNK(list_curr->type))
		ft_printf(" -> %s", list_curr->link_path);
}

void	display_extended_attr(t_entry *list_curr, t_args *pargs)
{
	int		i;

	if (list_curr->has_xattr > 0 && ft_iscinstr(pargs->flags, '@'))
	{
		i = 0;
		ft_printf("\n");
		while (list_curr->xattr[i])
		{
			ft_printf("        %s", list_curr->xattr[i]);
			print_spaces(28 - ft_strlen(list_curr->xattr[i]) -
						num_length(list_curr->xattr_sizes[i]));
			ft_printf("%d\n", list_curr->xattr_sizes[i]);
			i++;
		}
	}
	else
		ft_printf("\n");
}

void	print_type(t_entry *list_curr)
{
	if (S_ISREG(list_curr->type))
		ft_printf("-");
	if (S_ISDIR(list_curr->type))
		ft_printf("d");
	if (S_ISLNK(list_curr->type))
		ft_printf("l");
	if (S_ISBLK(list_curr->type))
		ft_printf("b");
	if (S_ISCHR(list_curr->type))
		ft_printf("c");
	if (S_ISSOCK(list_curr->type))
		ft_printf("s");
	if (S_ISFIFO(list_curr->type))
		ft_printf("p");
}
