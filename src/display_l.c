/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_l.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:02:12 by nkellum           #+#    #+#             */
/*   Updated: 2019/06/26 18:51:19 by jmondino         ###   ########.fr       */
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
	if (S_ISFIFO(list_current->type))
		printf("p");
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
		 || pShit->files[0]) && (!S_ISREG(pStat.st_mode)) 
		&& !ft_iscinstr(pShit->flags, 'd'))
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
