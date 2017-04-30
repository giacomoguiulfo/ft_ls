/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 00:44:09 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/30 04:50:50 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <stdio.h>

// S_IFMT
// type of file
// S_IFBLK
// block special
// S_IFCHR
// character special
// S_IFIFO
// FIFO special
// S_IFREG
// regular
// S_IFDIR
// directory
// S_IFLNK
// symbolic link

void print_type(mode_t mode)
{
	int bits;

	bits = (mode & S_IFMT);
	if (bits == S_IFDIR)
		putchar('d');
	else if (bits == S_IFCHR)
		putchar('c');
	else if (bits == S_IFBLK)
		putchar('b');
	else if (bits == S_IFLNK)
		putchar('l');
	else if (bits == S_IFSOCK)
		putchar('s');
	else if (bits == S_IFIFO)
		putchar('f');
	else
		putchar('-');
}

void print_permissions(mode_t mode)
{
	putchar((mode & S_IRUSR) ? 'r' : '-');
	putchar((mode & S_IWUSR) ? 'w' : '-');
	putchar((mode & S_IXUSR) ? 'x' : '-');
	putchar((mode & S_IRGRP) ? 'r' : '-');
	putchar((mode & S_IWGRP) ? 'w' : '-');
	putchar((mode & S_IXGRP) ? 'x' : '-');
	putchar((mode & S_IROTH) ? 'r' : '-');
	putchar((mode & S_IWOTH) ? 'w' : '-');
	putchar((mode & S_IXOTH) ? 'x' : '-');
}

void ls_time(time_t f_time)
{
	// char **all;
	// int i = 0;
	//
	// all = ft_strsplit(ctime(&f_time), ' ');
	// while (all[i])
	// 	printf("[i]: %s\n", all[i++]);
	// return (all[--i]); // Change to ft_printf
	time_t now;
	time_t dn;
	time_t diff;
	time_t beg = 0;

	now = time(NULL);
	printf("NOW:  [%ld]\n", now);
	printf("FILE: [%ld]\n", f_time);
	printf("DIFF: [%ld]\n", now - f_time);
	dn = now - f_time + now;
	// diff = labs(now - f_time);
	diff = labs(f_time - now);
	printf("D + N: [%ld]\n", dn);
	printf("C-NOW:   [%s]\n", ctime(&now));
	printf("C-FILE:  [%s]\n", ctime(&f_time));
	printf("C-DIFF:  [%s]\n", ctime(&diff));
	printf("C-6MAGO: [%s]\n", ctime(&dn));
	printf("Beg [%s]\n", ctime(&beg));

}

int	main(int argc, char **argv)
{
	if (argc != 2) return (0);
	/* Program */

	struct passwd *pwd;
	struct stat statbuf;
	struct group   *grp;

	printf("Name: %s\n", argv[1]);
	lstat(argv[1], &statbuf);
	printf("total %lld\n", statbuf.st_blocks);
	printf("Type: ");
	print_type(statbuf.st_mode);
	printf("\nModes: ");
	print_permissions(statbuf.st_mode);
	printf("\nNumber of links: %4d\n", statbuf.st_nlink);
	if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
		printf("Owner: %-8.8s\n", pwd->pw_name);
	else
		printf("Owner: %-8d\n", statbuf.st_uid);
	if ((grp = getgrgid(statbuf.st_gid)) != NULL)
		printf("Group: %-8.8s\n", grp->gr_name);
	else
		printf("Group: %-8d\n", statbuf.st_gid);
	printf("Size: %9jd\n", (intmax_t)statbuf.st_size);
	printf("stime: %ld\n", statbuf.st_mtime);
	// printf("ctime(): %s\n", ctime(&statbuf.st_mtime));
	ls_time(statbuf.st_mtimespec.tv_sec);
	return (0);
}

void	ls_file_handle(t_dnarr *files)
{
	int i;
	int padding[4];

	i = 0;
	ft_bzero(padding, sizeof(int) * 4);
	while (i < files->end)
		ls_padding_l(padding, ((t_file *)files->contents[i++])->statbuf);
	ft_qsort(files->contents, 0, dnarr_count(files) - 1, (t_sortcast) ft_strcmp);
	i = 0;
	if (g_ls_opts & OPT_l)
	{
		while (i < files->end)
			ls_file_l((t_file *)files->contents[i++], padding);
	}
	else
	{
		while (i < files->end)
			ft_printf("%s\n", (char *)files->contents[i++]);
	}
}
