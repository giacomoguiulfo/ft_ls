/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 08:50:51 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/30 19:47:13 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

extern int g_ls_opts;

void	ls_file_l(t_file *file, int *padding, char *name)
{
	struct passwd	*pwd;
	struct group	*grp;

	ls_print_type(file->statbuf.st_mode);
	ls_print_permissions(file->statbuf.st_mode);
	ft_putstr(listxattr(file->path, 0, 0, XATTR_NOFOLLOW) > 0 ? "@" : " ");
	ft_printf(" %*d", padding[0], file->statbuf.st_nlink);
	if ((pwd = getpwuid(file->statbuf.st_uid)) != NULL)
		ft_printf(" %-*s", padding[1], pwd->pw_name);
	else
		ft_printf(" %-8d", file->statbuf.st_uid); // TODO: Do I need this else?
	if ((grp = getgrgid(file->statbuf.st_gid)) != NULL)
		ft_printf("  %-*s", padding[2], grp->gr_name);
	else
		ft_printf("  %-8d", file->statbuf.st_gid); // TODO: Do I need this else?
	ft_printf("  %*d", padding[3], (intmax_t)file->statbuf.st_size);
	ls_lm_time(file->statbuf.st_mtime);
	ft_printf(" %s", name); // TODO: Needs good formatting to difference
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
	i = -1;
	while (++i < len)
		ls_file_l((t_file *)files->contents[i], padding,
					((t_file *)files->contents[i])->name);

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

int		ls_dir_content(t_dnarr **files, char *path)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_file			*tmp;

	if ((dirp = opendir(path)) == NULL)
		return (-1);
	*files = dnarr_create(sizeof(t_file), 50);
	while ((dp = readdir(dirp)) != NULL)
	{
		if (dp->d_name[0] == '.' && !(g_ls_opts & OPT_a))
			continue ;
		tmp = dnarr_new(*files);
		ft_asprintf(&tmp->path, "%s/%s", path, dp->d_name); // TODO: Do I need another case for the root dir? Don't think so...
		tmp->name = ft_strdup(dp->d_name);
		if (lstat(tmp->path, &(tmp->statbuf)) == -1) // TODO: Test -> Do I really need this
		{
			free(tmp->path);
			free(tmp->name);
			dnarr_destroy(*files);
			closedir(dirp);
			return (-1);
		}
		dnarr_push(*files, tmp);
	}
	closedir(dirp);
	return (0);
}

int		ls_print_dir(char *path)
{
	t_dnarr *files = NULL;
	int i;

	i = 0;
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
	// ft_printf("I am here and path is: [%s]\n", ((t_file *)files->contents[i])->path);
	// ft_printf("I am here and name is: [%s]\n", ((t_file *)files->contents[i])->name);
	ft_ls_sort(files);
	// ft_printf("I am here and path is: [%s]\n", ((t_file *)files->contents[i])->path);
	// ft_printf("I am here and name is: [%s]\n", ((t_file *)files->contents[i])->name);
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
			if (S_ISDIR(((t_file *)files->contents[i])->statbuf.st_mode)
				&& !(ft_strcmp(((t_file *)files->contents[i])->name, ".") == 0
				|| ft_strcmp(((t_file *)files->contents[i])->name, "..") == 0))
			{
				// ft_printf("I am here and name is: [%s]\n", ((t_file *)files->contents[i])->name);
				// ft_printf("I am here and path is: [%s]\n", ((t_file *)files->contents[i])->path);
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
	dnarr_clrdestroy(files);
	return (0);
}
