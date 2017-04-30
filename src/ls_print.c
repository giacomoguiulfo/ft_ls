/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 08:50:51 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/30 03:49:21 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

extern int g_ls_opts;

// int	ft_isdir(mode_t mode) // TODO: Do I need this?
// {
// 	int			bits;
//
// 	bits = (mode & S_IFMT);
// 	if (bits == S_IFDIR)
// 		return (1);
// 	return (0);
// }

void	ls_file_l(t_file *file, int *padding)
{
	struct passwd	*pwd;
	struct group	*grp;

	ls_print_type(file->statbuf.st_mode);
	ls_print_permissions(file->statbuf.st_mode);
	ft_putstr(listxattr(file->path, 0, 0, XATTR_NOFOLLOW) > 0 ? "@" : " ");
	ft_printf(" %*d", padding[0], file->statbuf.st_nlink); // TODO: Needs good formatting
	if ((pwd = getpwuid(file->statbuf.st_uid)) != NULL)
		ft_printf(" %-*s", padding[1], pwd->pw_name); // TODO: Needs good formatting
	else
		ft_printf(" %-8d", file->statbuf.st_uid);
	if ((grp = getgrgid(file->statbuf.st_gid)) != NULL)
		ft_printf("  %-*s", padding[2], grp->gr_name); // TODO: Needs good formatting
	else
		ft_printf("  %-8d", file->statbuf.st_gid);
	ft_printf("  %*d", padding[3], (intmax_t)file->statbuf.st_size); // TODO: Needs good formatting
	ls_lm_time(file->statbuf.st_mtime);
	ft_printf(" %s", file->name); // TODO: Needs good formatting
	if (S_ISLNK(file->statbuf.st_mode))
		ls_print_link(file->path);
	ft_putchar('\n');
}

void	ls_dir_l(t_dnarr *files)
{
	long long	blocks;
	int			padding[4];
	int			len;
	int			i;

	ft_bzero(padding, sizeof(int) * 4);
	i = 0;
	blocks = 0;
	len = files->end;
	while (i < len)
	{
		ls_padding_l(padding, ((t_file *)files->contents[i])->statbuf);
		blocks += ((t_file *)files->contents[i++])->statbuf.st_blocks;
	}
	ft_printf("total %lld\n", blocks);
	i = 0;
	while (i < len)
		// ft_printf("%s\n", ((t_file *)files->contents[i++]));
		ls_file_l((t_file *)files->contents[i++], padding);

}

char	*ls_pathname(char *path)
{
	char *name;

	name = path;
	while (*path)
	{
		if (*path++ == '/')
			name = path;
	}
	return (name);
}

int		cmpfunc(void *a, void *b)
{
	char *str1;
	char *str2;

	str1 = ((t_file *)(a))->name;
	str2 = ((t_file *)(b))->name;
	return (ft_strcmp(str1, str2));
}

int		ls_dir_content(t_dnarr **files, char *path)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_file			*tmp = NULL;


// int i = 0;
	if ((dirp = opendir(path)) == NULL)
		return (-1);
	*files = dnarr_create(sizeof(t_file), 50); // TODO: t_file or t_file *
	while ((dp = readdir(dirp)) != NULL)
	{
		if (dp->d_name[0] == '.' && !(g_ls_opts & OPT_a))
			continue ;
		tmp = dnarr_new(*files);
		ft_asprintf(&tmp->path, "%s/%s", path, dp->d_name); // TODO: DO another case for the root dir
		tmp->name = ft_strdup(dp->d_name);
		if (lstat(tmp->path, &(tmp->statbuf)) == -1)
		{
			free(tmp->path);
			dnarr_destroy(*files);
			closedir(dirp);
			return (-1);
		}
		dnarr_push(*files, tmp);
		// free(tmp->path);
		// ft_printf("%s %d\n", "Here", i++);
	}
	// ft_printf("%s: %d\n", "Capacity", dnarr_count(*files));
	// ft_printf("%s: %d\n", "Max", dnarr_max(*files));
	closedir(dirp);
	return (0);
}

int		ls_print_dir(char *path)
{
	t_dnarr *files = NULL;
	int i;

	i = 0;
	// files = dnarr_create(sizeof(t_file), 100); // TODO: t_file or t_file *
	if (ls_dir_content(&files, path) == -1)
	{
		ft_dprintf(2, "ls: %s: %s\n", ls_pathname(path), strerror(errno));
		return (-1);
	}
	if (files->end == 0)
	{
		dnarr_clrdestroy(files);
		return (-1);
	}
	// ft_printf("Debug: %s\n", );
	// ft_bubblesort(files->contents, sizeof(void *), dnarr_count(files) - 1, (comps) cmpfunc);
	// qsort(files->contents, dnarr_count(files), sizeof(void *), (t_sortcast) cmpfunc);
	// ft_qsort(files->contents, dnarr_count(files) - 1, sizeof(void *), (comps) cmpfunc);
	ft_qsort(files->contents, 0, dnarr_count(files) - 1, (t_sortcast) cmpfunc);
	if (g_ls_opts & OPT_l)
		ls_dir_l(files);
	else
		while (i < files->end)
			ft_printf("%s\n", ((t_file *)files->contents[i++])->name);
	if (g_ls_opts & OPT_R)
	{
		i = 0;
		while (i < files->end)
		{
			// printf("%s\n", "hello");
			// ft_printf("Current Name: %s\n", ((t_file *)files->contents[i])->name);;
			// ft_printf("Current Path: %s\n", ((t_file *)files->contents[i])->path);;
			// printf("Is dir? %d\n", ft_isdir(((t_file *)files->contents[i])->statbuf.st_mode));
			// ft_printf("Is dir? %d\n", ((t_file *)files->contents[i])->statbuf.st_mode);
			// ft_printf("Is dir? %d\n", S_ISDIR(((t_file *)files->contents[i])->statbuf.st_mode));

			if (S_ISDIR(((t_file *)files->contents[i])->statbuf.st_mode)
				&& !(ft_strcmp(((t_file *)files->contents[i])->name, ".") == 0
				|| ft_strcmp(((t_file *)files->contents[i])->name, "..") == 0))
			{
				// ft_printf("%s\n", "hello");
				ft_printf("\n%s:\n", ((t_file *)files->contents[i])->path);
				ls_print_dir(((t_file *)files->contents[i])->path);
			}
			++i;
		}
	}
	i = -1;
	while (++i < files->end)
	{
		free(((t_file *)files->contents[i])->path);
		free(((t_file *)files->contents[i])->name);
	}
	// TODO: Make another one of this ones for ->name
	// ft_printf("Current Name: %s\n", ((t_file *)files->contents[i])->name);;
	// ft_printf("Current Path: %s\n", ((t_file *)files->contents[i])->path);;
	// ft_printf("------------------------- END: %d\n", files->end);
	// ft_printf("------------------------- MAX: %d\n", files->max);
	// dnarr_clrdestroy(files);
	// free(files->contents[0]);
	i = 0;
	// while (i < files->end)
	// 	free(files->contents[i++]);
	// free(files->contents);
	// free(files);
	dnarr_clr(files);
	dnarr_destroy(files);
	// free(files);
	// for (int j = 0; j < files->end; j++)
	// {
	// 	// if (files->contents[i])
	// 		// free(files->contents[i]);
	// }
	return (0);
}
