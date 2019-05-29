/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:58:28 by nkellum           #+#    #+#             */
/*   Updated: 2019/05/29 12:50:25 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <dirent.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct 	s_entry
{
	char		*name;
	char		*rights;
	int			hard_links;
	char		*user;
	char		*group;
	int			size;
	char		*date_month_modified;
	int			date_day_modified;
	char		*date_time_modified;
	char		*date_month_created;
	int			date_day_created;
	char		*date_time_created;
	char		*date_month_accessed;
	int			date_day_accessed;
	char		*date_time_accessed;
}				t_entry;


#endif
