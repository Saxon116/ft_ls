/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:58:28 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/02 16:14:47 by jmondino         ###   ########.fr       */
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
# include <sys/xattr.h>
# include <sys/acl.h>
# include "libft.h"

# define RESET          "\033[0m"
# define RED            "\033[31m"
# define GREEN          "\033[32m"
# define BLUE           "\033[34m"
# define MAGENTA        "\033[35m"
# define BOLDMAGENTA    "\033[1;35m"
# define BOLDCYAN       "\033[1;36m"
# define BOLDWHITE      "\033[1;37m"
# define YELLOWBLUE		"\033[34;43m"
# define BLUEBLUE		"\033[34;46m"
# define BOLDCYANGREEN	"\033[1;36;42m"
# define SIXMONTHS		15778800

typedef struct 			s_args
{
	char				*flags;
	char				**dsfs;
	char				**newav;
	char				**files;
	char				**dirs;
	int					subdir;
	int					error;
}						t_args;

typedef struct 			s_entry
{
	int					type;
	char				*name;
	char				*rights;
	int					hard_links;
	char				*user;
	char				*group;
	int					size;
	int					block_size;
	char				*date_month_modified;
	int					date_day_modified;
	char				*date_time_modified;
	long				date_accessed;
	char				*link_path;
	long				mtime;
	int					has_xattr;
	int					has_acl;
	char				**xattr;
	int					*xattr_sizes;
	int					minor;
	int					major;
	struct s_entry		*next;
}						t_entry;

void		fill_date_time(t_entry *entry, struct stat pstat, int ut_flags);
t_entry    	*fill_list_rdir(DIR *pdir, t_args *pargs, char *path, char *dirname);
int			get_xattr_num(char *attributes, int size);
void		print_row(t_entry *lst_st, int ijpercol, char **array, int col_wid_j);
void		display_extended_attr(t_entry *list_curr, t_args *pargs);
void		display_last_entries(t_entry *list_curr, int *offsets);
void		display_first_entries(t_entry *list_curr, t_args *pargs, int *offsets);
void		free_pargs(t_args *pargs);
int			check_dir_a(char *name);
void		print_rows(char **array, int *wds, int col, t_entry *lst_st);
void		sort_longest_entries(int n, int *longest_entries);
int			get_all_names_length(t_entry *lst_st);
void		get_basic_offsets(int  **offsets, t_entry *list_curr);
void		free_columns(char **array);
void		print(t_entry *lst_st);
int			get_all_names_lentgh(t_entry *lst_st);
void		print_rows(char **array, int *wds, int col, t_entry *lst_st);
void		ft_asciiorder(char **tab);
void		ft_accessorder(char **tab);
int			fill_newav(char **av, t_args *pargs, char **tmp, int j);
void		ft_revtab(char **tab);
void    	lstdel(t_entry **lst);
void		ft_parseargs(char **av, t_args *pargs);
void		ft_fillpargs(char *flags, char **newav, int index, t_args *pargs);
void		print_spaces(int num);
void		display_entries_l(t_entry *lst_st, t_args *pargs, char *dirname);
void		ft_display(t_args *pargs);
void		list_dir_recursive(char *dirname, char *name, t_args *pargs);
void		ft_print_dir_name(t_entry *lst_st, t_args *pargs, char *dirname);
void		ft_total(t_entry *lst_st, t_args *pargs, char *dirname);
void		ft_swap(t_entry *a, t_entry *b);
void		ft_rev_list(t_entry **list);
void		ft_fill(t_entry *fill, t_entry *src);
void		ft_timeorder(char **tab);
void    	print_color(char *entry, int type, char *rights);
void    	print_color_l(char *entry, int type, char *rights);
void    	display_normally(t_args *pargs, int i);
void    	ft_display_d(t_args *pargs);
void    	print_type(t_entry *list_curr);
char		*ft_checkflags(char *str);
char		*permissions(mode_t perm);
char		**ft_isfile(char **newav, int index, t_args *pargs);
char		**ft_isdir(char **newav, int index);
char 		*get_link_path(char *path);
char 		**get_xattr_list(char *attributes, int size);
int			ft_existent(char *str, t_args *pargs);
int			ft_existent2(char *str);
int 		get_day(char *date);
int 		num_length(long long num);
int 		has_acl(char *path);
int 		*get_offsets(t_entry *lst_st);
int 		*get_xattr_sizes(char **attributes, char *path, int length);
t_args		*initstru(char **av);
t_entry 	*fill_list(DIR *pdir, t_args *pargs, char *path, char *dirname);
t_entry 	*fill_list_a(DIR *pdir, t_args *pargs, char *path, char *dirname);
t_entry 	*add_new_entry(char *path, char *entry_name, t_args *pargs);
t_entry     *ft_tri_ascii(t_entry *list, t_args *pargs);
t_entry     *ft_tri_date(t_entry *list, t_args *pargs);
t_entry     *fill_tmp(void);
t_entry     *fill_list_d(t_args *pargs);
t_entry    *ft_tri_access(t_entry *list, t_args *pargs);
void		ft_print_column(t_entry *lst_st);
int			get_list_size(t_entry *lst_st);
int			num_columns(t_entry *lst_st, int terminal_width);
char		**array_from_list(t_entry *lst_st);
int			*get_column_widths(char **array, int num_columns, int list_size);
void		print_normally(t_entry *lst_st);
int			longest_in_column(char **array, int start, int end, int list_size);
int			get_xattr_num(char *attributes, int size);

#endif
