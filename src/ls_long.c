/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:43:34 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/05/03 23:10:19 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

extern long int g_ls_opts;

static inline time_t	ls_get_time(t_file *file)
{
	if (g_ls_opts & OPT_c)
		return (file->statbuf.st_ctime);
	else if (g_ls_opts & OPT_u)
		return (file->statbuf.st_atime);
	else if (g_ls_opts & OPT_U)
		return (file->statbuf.st_birthtime);
	else
		return (file->statbuf.st_mtime);
}

static void				ls_lm_time(t_file *file)
{
	char	*tmp;
	time_t	currtime;
	time_t	var_time;

	var_time = ls_get_time(file);
	currtime = time(0);
	tmp = ctime(&var_time);
	if (g_ls_opts & OPT_T)
		ft_printf(" %2.2s %3.3s %8.8s %4.4s", &tmp[8], &tmp[4], &tmp[11],
																	&tmp[20]);
	else if (ABS(currtime - var_time) > 15770000)
		ft_printf(" %2.2s %3.3s  %4.4s", &tmp[8], &tmp[4], &tmp[20]);
	else
		ft_printf(" %2.2s %3.3s %5.5s", &tmp[8], &tmp[4], &tmp[11]);
}

static int				ls_print_type(mode_t mode)
{
	int bits;

	bits = (mode & S_IFMT);
	if (bits == S_IFDIR)
		write(1, "d", 1);
	else if (bits == S_IFCHR)
	{
		write(1, "c", 1);
		return (1);
	}
	else if (bits == S_IFBLK)
	{
		write(1, "b", 1);
		return (1);
	}
	else if (bits == S_IFLNK)
		write(1, "l", 1);
	else if (bits == S_IFSOCK)
		write(1, "s", 1);
	else if (bits == S_IFIFO)
		write(1, "f", 1);
	else
		write(1, "-", 1);
	return (0);
}

static inline void		ls_print_permissions(mode_t mode)
{
	write(1, (mode & S_IRUSR) ? "r" : "-", 1);
	write(1, (mode & S_IWUSR) ? "w" : "-", 1);
	if (mode & S_ISUID)
		write(1, (mode & S_IXUSR) ? "s" : "S", 1);
	else
		write(1, (mode & S_IXUSR) ? "x" : "-", 1);
	write(1, (mode & S_IRGRP) ? "r" : "-", 1);
	write(1, (mode & S_IWGRP) ? "w" : "-", 1);
	if (mode & S_ISGID)
		write(1, (mode & S_IXGRP) ? "s" : "S", 1);
	else
		write(1, (mode & S_IXGRP) ? "x" : "-", 1);
	write(1, (mode & S_IROTH) ? "r" : "-", 1);
	write(1, (mode & S_IWOTH) ? "w" : "-", 1);
	if (mode & S_ISVTX)
		write(1, (mode & S_IXOTH) ? "t" : "T", 1);
	else
		write(1, (mode & S_IXOTH) ? "x" : "-", 1);
}

void					ls_file_l(t_file *file, int *padding, char *name)
{
	struct passwd	*pwd;
	struct group	*grp;
	int				device;

	device = ls_print_type(file->statbuf.st_mode);
	ls_print_permissions(file->statbuf.st_mode);
	ft_putstr(listxattr(file->path, 0, 0, XATTR_NOFOLLOW) > 0 ? "@" : " ");
	ft_printf(" %*d ", padding[0], file->statbuf.st_nlink);
	if (!(g_ls_opts & OPT_g))
		if ((pwd = getpwuid(file->statbuf.st_uid)) != NULL)
			ft_printf("%-*s  ", padding[1], pwd->pw_name);
	if (!(g_ls_opts & OPT_o))
		if ((grp = getgrgid(file->statbuf.st_gid)) != NULL)
			ft_printf("%-*s  ", padding[2], grp->gr_name);
	if (g_ls_opts & OPT_o && g_ls_opts & OPT_g)
		ft_putstr("  ");
	if (!device)
		ft_printf("%*jd", padding[3], (intmax_t)file->statbuf.st_size);
	else
		ft_printf("  %ld, %ld", (long)major(file->statbuf.st_rdev),
								(long)minor(file->statbuf.st_rdev));
	ls_lm_time(file);
	ft_printf(" %s", name);
	if (S_ISLNK(file->statbuf.st_mode))
		ls_print_link(file->path);
}
