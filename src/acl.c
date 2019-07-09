/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:45:29 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/09 16:14:03 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		has_acl(char *path)
{
	acl_t			acl;
	acl_entry_t		dummy;

	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	if (acl != NULL)
	{
		acl_free(acl);
		return (1);
	}
	else
	{
		acl_free(acl);
		return (0);
	}
}

void	print_spaces(int num)
{
	int				i;

	i = 0;
	while (i < num)
	{
		ft_printf(" ");
		i++;
	}
}
