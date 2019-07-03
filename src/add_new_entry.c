/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_entry.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 12:22:33 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/03 15:19:23 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		fill_entry(t_entry *entry, struct stat pstat, int ut_flags)
{
	entry->type = pstat.st_mode;
	if (S_ISBLK(entry->type) || S_ISCHR(entry->type))
	{
		entry->minor = minor(pstat.st_rdev);
		entry->major = major(pstat.st_rdev);
	}
	entry->rights = permissions(pstat.st_mode);
	entry->hard_links = pstat.st_nlink;
	entry->size = pstat.st_size;
	fill_usr_grp(entry, pstat);
	entry->date_day_modified = get_day(ctime(ut_flags ?
			&pstat.st_atimespec.tv_sec : &pstat.st_mtimespec.tv_sec));
	entry->block_size = pstat.st_blocks;
	entry->date_month_modified = ft_strsub(ctime(ut_flags ?
			&pstat.st_atimespec.tv_sec : &pstat.st_mtimespec.tv_sec), 4, 3);
	entry->mtime = pstat.st_mtime;
	fill_date_time(entry, pstat, ut_flags);
	entry->date_accessed = pstat.st_atimespec.tv_sec;
	entry->next = NULL;
}

void		fill_usr_grp(t_entry *entry, struct stat pstat)
{
	if (getpwuid(pstat.st_uid))
		entry->user = ft_strdup(getpwuid(pstat.st_uid)->pw_name);
	else
		entry->user = ft_itoa(pstat.st_uid);
	if (getgrgid(pstat.st_gid))
		entry->group = ft_strdup(getgrgid(pstat.st_gid)->gr_name);
	else
		entry->group = ft_itoa(pstat.st_gid);
}

void		fill_date_time(t_entry *entry, struct stat pstat, int ut_flags)
{
	if ((time(0) - pstat.st_mtime) > SIXMONTHS)
	{
		entry->date_time_modified = ft_strsub(ctime(ut_flags ?
		&pstat.st_atimespec.tv_sec : &pstat.st_mtimespec.tv_sec), 20, 4);
	}
	else
	{
		entry->date_time_modified = ft_strsub(ctime(ut_flags ?
		&pstat.st_atimespec.tv_sec : &pstat.st_mtimespec.tv_sec), 11, 5);
	}
}

t_entry		*add_new_entry(char *path, char *entry_name, t_args *pargs)
{
	t_entry			*entry;
	struct stat		pstat;
	char			l[1024];
	int				ut_flags;

	ut_flags = (ft_iscinstr(pargs->flags, 't')
				&& ft_iscinstr(pargs->flags, 'u'));
	if ((entry = malloc(sizeof(t_entry))) == NULL)
		return (0);
	if (lstat(path, &pstat) == -1)
		return (0);
	entry->has_xattr = listxattr(path, l, 1024, XATTR_NOFOLLOW);
	if (entry->has_xattr)
	{
		entry->xattr = get_xattr_list(l, entry->has_xattr);
		entry->xattr_sizes = get_xattr_sizes(entry->xattr, path,
										get_xattr_num(l, entry->has_xattr));
	}
	entry->has_acl = has_acl(path);
	entry->link_path = get_link_path(path);
	entry->name = ft_strdup(entry_name);
	fill_entry(entry, pstat, ut_flags);
	return (entry);
}

char		*permissions(mode_t perm)
{
	char			*modeval;

	if ((modeval = malloc(sizeof(char) * 9 + 1)) == NULL)
		return (NULL);
	modeval[0] = (perm & S_IRUSR) ? 'r' : '-';
	modeval[1] = (perm & S_IWUSR) ? 'w' : '-';
	modeval[2] = (perm & S_IXUSR) ? 'x' : '-';
	modeval[3] = (perm & S_IRGRP) ? 'r' : '-';
	modeval[4] = (perm & S_IWGRP) ? 'w' : '-';
	modeval[5] = (perm & S_IXGRP) ? 'x' : '-';
	modeval[6] = (perm & S_IROTH) ? 'r' : '-';
	modeval[7] = (perm & S_IWOTH) ? 'w' : '-';
	if ((perm & S_ISVTX))
		modeval[8] = 't';
	else
		modeval[8] = (perm & S_IXOTH) ? 'x' : '-';
	modeval[9] = '\0';
	return (modeval);
}
