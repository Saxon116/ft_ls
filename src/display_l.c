/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_l.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:02:12 by nkellum           #+#    #+#             */
/*   Updated: 2019/06/24 13:30:20 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		num_length(long long num)
{
	int			i;

	i = 0;
	if (num < 0)
	{
		num = -num;
		i++;
	}
	while (num /= 10)
		i++;
	i++;
	return (i);
}

int 	*get_offsets(t_entry *list_start)
{
	int 		*offsets;
	t_entry 	*list_current;

	if ((offsets = malloc(sizeof(int) * 5)) == NULL)
		return 0;
	offsets[0] = 0;
	offsets[1] = 0;
	offsets[2] = 0;
	offsets[3] = 0;
	offsets[4] = 0;
	list_current = list_start;
	while (list_current)
	{
		if (num_length(list_current->hard_links) > offsets[0])
			offsets[0] = num_length(list_current->hard_links);
		if (num_length(list_current->size) > offsets[1])
			offsets[1] = num_length(list_current->size);
		if (num_length(list_current->date_day_modified) > offsets[2])
			offsets[2] = num_length(list_current->date_day_modified);
		if (ft_strlen(list_current->user) > (unsigned) offsets[3])
			offsets[3] = ft_strlen(list_current->user);
		if (ft_strlen(list_current->group) > (unsigned) offsets[4])
			offsets[4] = ft_strlen(list_current->group);
		list_current = list_current->next;
	}
	return (offsets);
}

void	print_type(t_entry *list_current)
{
	if (S_ISREG(list_current->type))
		printf("-");
	if (S_ISDIR(list_current->type))
		printf("d");
	if (S_ISLNK(list_current->type))
		printf("l");
	if (S_ISBLK(list_current->type))
		printf("b");
	if (S_ISCHR(list_current->type))
		printf("c");
	if (S_ISSOCK(list_current->type))
		printf("s");
}

void 	display_entries_l(t_entry *list_start, t_shit *pShit, char *dirname)
{
	t_entry 	*list_current;
	int 		*offsets;

	ft_total(list_start, pShit, dirname);
	offsets = get_offsets(list_start);
	list_current = list_start;
	while (list_current)
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
		printf("%d %s", list_current->size, list_current->date_month_modified);
		print_spaces(offsets[2] - (num_length(list_current->date_day_modified)));
		printf(" %d %s ", list_current->date_day_modified,
			   list_current->date_time_modified);
		print_color_l(list_current->name, list_current->type, list_current->rights);
		if (S_ISLNK(list_current->type))
			printf(" -> %s", list_current->link_path);
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
		list_current = list_current->next;
	}
	free(offsets);
}

void	ft_total(t_entry *list_start, t_shit *pShit, char *dirname)
{
	struct stat pStat;
	t_entry 	*browse;
	int			total;
	int			i;

	lstat(dirname, &pStat);
	total = 0;
	i = 0;
	browse = list_start;
	if ((pShit->error != 0 || pShit->subdir != 0 || pShit->dirs[1]
		 || pShit->files[0]) && (!S_ISREG(pStat.st_mode)))
		printf("%s:\n", dirname);
	while (browse)
	{
		total += browse->block_size;
		browse = browse->next;
		i++;
	}
	if (i != 0 && (!S_ISREG(pStat.st_mode)) && !ft_iscinstr(pShit->flags, 'd'))
		printf("total %d\n", total);
}
