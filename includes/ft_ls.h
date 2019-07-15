/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:58:28 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/15 18:33:15 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

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
# include "../ft_printf/ft_printf.h"

# define RESET			"\033[0m"
# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define BLUE			"\033[34m"
# define MAGENTA		"\033[35m"
# define BOLDMAGENTA	"\033[1;35m"
# define BOLDCYAN		"\033[1;36m"
# define BOLDWHITE		"\033[1;37m"
# define YELLOWBLUE		"\033[34;43m"
# define BLUEBLUE		"\033[34;46m"
# define BOLDCYANGREEN	"\033[1;36;42m"
# define REDBLACK		"\033[30;41m"
# define SIXMONTHS		15778800

typedef struct			s_args
{
	char				*flags;
	char				**dsfs;
	char				**newav;
	char				**files;
	char				**dirs;
	int					subdir;
	int					error;
}						t_args;

typedef struct			s_entry
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

/*
**						acl. c
*/
int						has_acl(char *path);
void					print_spaces(int num);

/*
**						add_new_entry.c
*/
void					fill_entry(t_entry *entry, struct stat pstat,
										int ut_flags);
void					fill_usr_grp(t_entry *entry, struct stat pstat);
void					fill_date_time(t_entry *entry, struct stat pstat,
										int ut_flags);
t_entry					*add_new_entry(char *path, char *entry_name,
										t_args *pargs);
char					*permissions(mode_t perm);

/*
**						add_new_entry_aux.c
*/
char					*get_link_path(char *path);
int						get_day(char *date);
void					p_denied(t_args *pargs, char *path, char *name);
char					ext_permissions(mode_t perm, int modeval);

/*
**						column.c
*/
void					ft_print_column(t_entry *lst_st);
int						*get_column_widths(char **array, int num_columns,
											int list_size);
int						longest_in_column(char **array, int start, int end,
											int list_size);
int						num_columns(t_entry *lst_st, int terminal_width);
void					print_row(t_entry *lst_st, int ijpercol, char **array,
									int col_wid_j);

/*
**						column_aux.c
*/
int						get_all_names_length(t_entry *lst_st);
int						get_list_size(t_entry *lst_st);
void					sort_longest_entries(int n, int *longest_entries);
char					**array_from_list(t_entry *lst_st);
void					print_rows(char **array, int *wds, int col,
									t_entry *lst_st);

/*
**						display.c
*/
void					ft_display(t_args *pargs);
void					display_normally(t_args *pargs, int i);
void					ft_display_d(t_args *pargs);

/*
**						fill_list.c
*/
t_entry					*fill_list_d(t_args *pargs);
t_entry					*fill_list_rdir(DIR *pdir, t_args *pargs, char *path,
										char *dirname);
t_entry					*fill_list(DIR *pdir, t_args *pargs, char *path,
									char *dirname);
t_entry					*fill_list_a(DIR *pdir, t_args *pargs, char *path,
									char *dirname);
int						check_dir_a(char *name);

/*
**						fill_list_aux.c
*/
t_entry					*fill_it(t_args *pargs);

/*
**						free.c
*/
void					lstdel(t_entry **lst);
void					free_columns(char **array);
void					free_pargs(t_args *pargs);

/*
**						offsets.c
*/
void					get_special_offsets(int **offsets, t_entry *list_curr);
int						*get_offsets(t_entry *lst_st);
void					get_basic_offsets(int **offsets, t_entry *list_curr);
int						num_length(long long num);

/*
**						parsing.c
*/
void					ft_parseargs(char **av, t_args *pargs);
char					**ft_isdir(char **newav, int index);
char					**ft_isfile(char **newav, int index, t_args *pargs);
int						ft_existent(char *str, t_args *pargs);
int						ft_existent2(char *str);

/*
**						parsing_aux.c
*/
char					*ft_checkflags(char *str);
int						fill_newav(char **av, t_args *pargs, char **tmp, int j);
void					ft_fillpargs(char *flags, char **newav, int index,
									t_args *pargs);
t_args					*initstru(char **av);
void					fill_dsfs(t_args *pargs);

/*
**						print_color.c
*/
void					print(t_entry *lst_st);
void					print_color_l(char *entry, int type, char *rights);
void					print_color(char *entry, int type, char *rights);

/*
**						print_l.c
*/
void					display_entries_l(t_entry *lst_st, t_args *pargs,
											char *dirname);
void					display_first_entries(t_entry *list_curr, t_args *pargs,
												int *offsets);
void					display_last_entries(t_entry *list_curr, int *offsets);
void					display_extended_attr(t_entry *list_curr,
												t_args *pargs);
void					print_type(t_entry *list_curr);

/*
**						print_l_aux.c
*/
void					ft_total(t_entry *lst_st, t_args *pargs, char *dirname);

/*
**						recursive.c
*/
void					ft_print_dir_name(t_entry *lst_st, t_args *pargs,
											char *dirname);
void					list_dir_recursive(char *dirname, char *name,
											t_args *pargs);
void					cycle_subdirs(t_args *pargs,
												char *path, char *dirname);

/*
**						sort_list.c
*/
t_entry					*ft_tri_date(t_entry *list, t_args *pargs);
t_entry					*ft_tri_access(t_entry *list, t_args *pargs);
t_entry					*ft_tri_ascii(t_entry *list, t_args *pargs);
void					ft_rev_list(t_entry **list);

/*
**						sort_list_aux.c
*/
void					ft_swap(t_entry *a, t_entry *b);
void					ft_fill(t_entry *fill, t_entry *src);

/*
**						sort_tab.c
*/
void					ft_accessorder(char **tab);
void					ft_timeorder(char **tab);
void					ft_asciiorder(char **tab);
void					ft_revtab(char **tab);

/*
**						xattr.c
*/
int						get_xattr_num(char *attributes, int size);
char					**get_xattr_list(char *attributes, int size);
int						*get_xattr_sizes(char **attributes, char *path,
										int length);

#endif
