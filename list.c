/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 02:06:51 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/24 02:37:33 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdio.h>
#include <stdint.h>


int main(int argc, char **argv)
{
	if (argc != 2) return (0);

	struct dirent  *dp;
	struct stat     statbuf;
	struct passwd  *pwd;
	struct group   *grp;
	struct tm      *tm;
	char            datestring[256];
	DIR *dir;
	char	path[1024];

	dir = opendir(argv[1]);
	/* Loop through directory entries. */
	while ((dp = readdir(dir)) != NULL)
	{
		/* Get entry's information. */
		// if (stat(dp->d_name, &statbuf) == -1)
		// 	continue;
		sprintf(path, "%s/%s", argv[1], dp->d_name);
		lstat(path, &statbuf);

		/* Print out type, permissions, and number of links. */
		printf("%4d", statbuf.st_nlink);

		/* Print out owner's name if it is found using getpwuid(). */
		if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
			printf(" %-8.8s", pwd->pw_name);
		else
			printf(" %-8d", statbuf.st_uid);

		/* Print out group name if it is found using getgrgid(). */
		if ((grp = getgrgid(statbuf.st_gid)) != NULL)
			printf(" %-8.8s", grp->gr_name);
		else
			printf(" %-8d", statbuf.st_gid);

		/* Print size of file. */
		printf(" %9jd", (intmax_t)statbuf.st_size);

		tm = localtime(&statbuf.st_mtime);

		/* Get localized date string. */
		strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);

		printf(" %s %s\n", datestring, dp->d_name);
	}
}
