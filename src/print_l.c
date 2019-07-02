/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:25:09 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/02 17:06:01 by jmondino         ###   ########.fr       */
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
	printf("%s", list_curr->rights);
	if (list_curr->has_xattr > 0)
		printf("@ ");
	else if (list_curr->has_acl)
		printf("+ ");
	else
		printf("  ");
	print_spaces(offsets[0] - (num_length(list_curr->hard_links)));
	printf("%d", list_curr->hard_links);
	if (!ft_iscinstr(pargs->flags, 'g'))
	{
		printf(" %s ", list_curr->user);
		print_spaces(offsets[3] - (ft_strlen(list_curr->user)));
	}
	printf(" %s  ", list_curr->group);
	print_spaces(offsets[4] - (ft_strlen(list_curr->group)));
	print_spaces(offsets[1] - (num_length(list_curr->size)));
}

void	display_last_entries(t_entry *list_curr, int *offsets)
{
	if (S_ISBLK(list_curr->type) || S_ISCHR(list_curr->type))
	{
		print_spaces(offsets[5] - num_length(list_curr->major));
		printf("%d, ", list_curr->major);
		print_spaces(offsets[6] - num_length(list_curr->minor));
		printf("%d ", list_curr->minor);
	}
	else
	{
		print_spaces(offsets[7] + 2);
		printf("%d ", list_curr->size);
	}
	printf("%s", list_curr->date_month_modified);
	print_spaces(offsets[2] - (num_length(list_curr->date_day_modified)));
	printf(" %d", list_curr->date_day_modified);
	if (ft_strlen(list_curr->date_time_modified) == 4)
		print_spaces(1);
	printf(" %s ", list_curr->date_time_modified);
	print_color_l(list_curr->name, list_curr->type, list_curr->rights);
	if (S_ISLNK(list_curr->type))
		printf(" -> %s", list_curr->link_path);
}

void	display_extended_attr(t_entry *list_curr, t_args *pargs)
{
	int		i;

	if (list_curr->has_xattr > 0 && ft_iscinstr(pargs->flags, '@'))
	{
		i = 0;
		printf("\n");
		while (list_curr->xattr[i])
		{
			printf("        %s", list_curr->xattr[i]);
			print_spaces(28 - ft_strlen(list_curr->xattr[i]) -
						num_length(list_curr->xattr_sizes[i]));
			printf("%d\n", list_curr->xattr_sizes[i]);
			i++;
		}
	}
	else
		printf("\n");
}

void	print_type(t_entry *list_curr)
{
	if (S_ISREG(list_curr->type))
		printf("-");
	if (S_ISDIR(list_curr->type))
		printf("d");
	if (S_ISLNK(list_curr->type))
		printf("l");
	if (S_ISBLK(list_curr->type))
		printf("b");
	if (S_ISCHR(list_curr->type))
		printf("c");
	if (S_ISSOCK(list_curr->type))
		printf("s");
	if (S_ISFIFO(list_curr->type))
		printf("p");
}
