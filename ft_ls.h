/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:58:28 by nkellum           #+#    #+#             */
/*   Updated: 2019/05/29 17:51:29 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>
#include <time.h>
#include "libft/libft.h"

typedef struct 	s_entry
{
	int				is_folder;
	char			*name;
	char			*rights;
	int				hard_links;
	char			*user;
	char			*group;
	int				size;
	char			*date_month_modified;
	int				date_day_modified;
	char			*date_time_modified;
	long			date_accessed;
	struct s_entry	*next;
}				t_entry;


#endif
