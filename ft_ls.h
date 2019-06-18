/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:58:28 by jmondino          #+#    #+#             */
/*   Updated: 2019/06/18 16:25:00 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <dirent.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <errno.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <time.h>
# include <sys/ioctl.h>
# include "libft/libft.h"

# define OP(x) x == 'a' || x == 'r' || x == 'l' || x == 'R' || x == 't'

typedef struct 		s_shit
{
	char			*flags;
	char			**files;
	char			**dirs;
	int				subdir;
	int				error;
}					t_shit;

typedef struct 	s_entry
{
	int				type;
	char			*name;
	char			*rights;
	int				hard_links;
	char			*user;
	char			*group;
	int				size;
	int				block_size;
	char			*date_month_modified;
	int				date_day_modified;
	char			*date_time_modified;
	long			date_accessed;
	char			*link_path;
	long			mtime;
	struct s_entry	*next;
}				t_entry;

void		ft_asciiorder(char **tab);
void		ft_revtab(char **tab);
void    	lstdel(t_entry **lst);
void		ft_parseargs(char **av, t_shit *pShit);
void		ft_fillpShit(char *flags, char **newav, int index, t_shit *pShit);
void 		print_spaces(int num);
void 		display_entries_l(t_entry *list_start, t_shit *pShit, char *dirname);
void		ft_display(t_shit *pShit);
void 		list_dir_recursive(char *dirname, t_shit *pShit);
void		ft_print_dir_name(t_entry *list_start, t_shit *pShit, char *dirname);
void		ft_total(t_entry *list_start, t_shit *pShit, char *dirname);
void		ft_swap(t_entry *a, t_entry *b);
void		ft_rev_list(t_entry **list);
void		ft_fill(t_entry *fill, t_entry *src);
void		ft_timeorder(char **tab);
char		*ft_checkflags(char *str);
char 		*permissions(mode_t perm);
char		**ft_isfile(char **newav, int index, t_shit *pShit);
char		**ft_isdir(char **newav, int index, t_shit *pShit);
int			ft_existent(char *str, int here, t_shit *pShit);
int 		get_day(char *date);
int 		num_length(long long num);
int 		*get_offsets(t_entry *list_start);
t_shit		*initstru(void);
t_entry 	*fill_list(DIR *pDir, struct dirent *pDirent, char *path, char *dirname);
t_entry     *fill_list_a(DIR *pDir, struct dirent *pDirent, char *path, char *dirname);
t_entry 	*add_new_entry(char *path, char *entry_name, int is_folder);
t_entry     *ft_tri_ascii(t_entry *list, t_shit *pShit);
t_entry     *ft_tri_date(t_entry *list, t_shit *pShit);
t_entry     *fill_tmp(void);
t_entry     *add_new_entry2(char *entry_name);

#endif
