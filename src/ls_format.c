/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 19:54:11 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/30 19:43:29 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void ls_print_type(mode_t mode)
{
	int bits;

	bits = (mode & S_IFMT);
	if (bits == S_IFDIR)
		ft_putchar('d');
	else if (bits == S_IFCHR)
		ft_putchar('c');
	else if (bits == S_IFBLK)
		ft_putchar('b');
	else if (bits == S_IFLNK)
		ft_putchar('l');
	else if (bits == S_IFSOCK)
		ft_putchar('s');
	else if (bits == S_IFIFO)
		ft_putchar('f');
	else
		ft_putchar('-');
}

void ls_print_permissions(mode_t mode)
{
	ft_putchar((mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((mode & S_IWUSR) ? 'w' : '-');
	if (mode & S_ISUID)
		ft_putchar((mode & S_IXUSR) ? 's' : 'S');
	else
		ft_putchar((mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((mode & S_IWGRP) ? 'w' : '-');
	if (mode & S_ISGID)
		ft_putchar((mode & S_IXGRP) ? 's' : 'S');
	else
		ft_putchar((mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((mode & S_IROTH) ? 'r' : '-');
	ft_putchar((mode & S_IWOTH) ? 'w' : '-');
	if (mode & S_ISVTX)
		ft_putchar((mode & S_IXOTH) ? 't' : 'T');
	else
		ft_putchar((mode & S_IXOTH) ? 'x' : '-');
}

void	ls_padding_l(int *padding, struct stat statbuf)
{
	padding[0] = MAX(padding[0], ft_nblen(statbuf.st_nlink));
	padding[1] = MAX(padding[1], (int)ft_strlen(getpwuid(statbuf.st_uid)->pw_name));
	padding[2] = MAX(padding[2], (int)ft_strlen(getgrgid(statbuf.st_gid)->gr_name));
	padding[3] = MAX(padding[3], ft_nblen(statbuf.st_size));
}

void	ls_lm_time(time_t var_time)
{
	char *tmp;
	time_t currtime;

	currtime = time(0);
	tmp = ctime(&var_time);
	if (ABS(currtime - var_time) > 15780000)
		ft_printf(" %2.2s %3.3s  %4.4s", &tmp[8], &tmp[4], &tmp[20]);
	else
		ft_printf(" %2.2s %3.3s %5.5s", &tmp[8], &tmp[4], &tmp[11]);
}

void	ls_print_link(char *path)
{
	char linkname[PATH_MAX + 1];

	ft_bzero(linkname, PATH_MAX + 1);
	readlink(path, linkname, PATH_MAX);
	ft_printf(" -> %s", linkname);
}
