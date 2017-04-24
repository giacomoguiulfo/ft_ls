/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 00:44:09 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/24 02:04:48 by gguiulfo         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	if (argc != 2) return (0);
	/* Program */
	
	struct passwd *pwd;
	struct stat statbuf;
	struct group   *grp;

	printf("Name: %s\n", argv[1]);
	lstat(argv[1], &statbuf);
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
	return (0);
}
