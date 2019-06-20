/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_l.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:02:12 by nkellum           #+#    #+#             */
/*   Updated: 2019/06/20 14:56:55 by nkellum          ###   ########.fr       */
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
	if (list_current->type == DT_REG)
		printf("-");
	if (list_current->type == DT_DIR)
		printf("d");
	if (list_current->type == DT_LNK)
		printf("l");
	if (list_current->type == DT_BLK)
		printf("b");
	if (list_current->type == DT_CHR)
		printf("c");
	if (list_current->type == DT_SOCK)
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
		printf("%s  ", list_current->rights);
		print_spaces(offsets[0] - (num_length(list_current->hard_links)));
		printf("%d %s", list_current->hard_links, list_current->user);
		print_spaces(offsets[3] - (ft_strlen(list_current->user)));
		printf("  %s  ", list_current->group);
		print_spaces(offsets[4] - (ft_strlen(list_current->group)));
		print_spaces(offsets[1] - (num_length(list_current->size)));
		printf("%d %s", list_current->size, list_current->date_month_modified);
		print_spaces(offsets[2] - (num_length(list_current->date_day_modified)));
		printf(" %d %s ", list_current->date_day_modified,
			   list_current->date_time_modified);
		print_color_l(list_current->name, list_current->type, list_current->rights);
		if (list_current->type == DT_LNK)
			printf(" -> %s", list_current->link_path);
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
	if (i != 0 && (!S_ISREG(pStat.st_mode)))
		printf("total %d\n", total);
}
