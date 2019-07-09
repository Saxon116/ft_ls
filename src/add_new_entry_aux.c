/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_entry_aux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:19:18 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/09 13:03:36 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*get_link_path(char *path)
{
	char		*buf;
	ssize_t		len;

	if ((buf = malloc(1024)) == NULL)
		return (NULL);
	len = readlink(path, buf, 1023);
	if (len != -1)
	{
		buf[len] = '\0';
		return (buf);
	}
	else
	{
		free(buf);
		return (ft_strdup(""));
	}
}

int			get_day(char *date)
{
	int			i;

	i = 0;
	if (date)
	{
		while (!ft_isdigit(date[i]))
			i++;
		return (ft_atoi(date + i));
	}
	return (0);
}

void		p_denied(t_args *pargs, char *path, char *name)
{
	if (pargs->subdir != 0 || pargs->dirs[1] || pargs->files[0]
		|| pargs->error != 0)
		printf("%s:\n", path);
	printf(RESET"ft_ls: %s: Permission denied\n", name);
}
