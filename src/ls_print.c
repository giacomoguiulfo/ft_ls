/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 08:50:51 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/05/03 23:11:44 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

extern long int g_ls_opts;

void				ls_dir_l(t_dnarr *files)
{
	long long	blocks;
	int			padding[4];
	int			i;

	i = 0;
	blocks = 0;
	ft_bzero(padding, sizeof(int) * 4);
	while (i < files->end)
	{
		ls_padding_l(padding, ((t_file *)files->contents[i])->statbuf);
		blocks += ((t_file *)files->contents[i++])->statbuf.st_blocks;
	}
	ft_printf("total %lld\n", blocks);
	i = -1;
	while (++i < files->end)
	{
		ls_file_l((t_file *)files->contents[i], padding,
					((t_file *)files->contents[i])->name);
		write(1, "\n", 1);
	}
}

static inline int	ls_free_dircont(t_file *tmp, t_dnarr **files, DIR *dirp)
{
	free(tmp->path);
	free(tmp->name);
	dnarr_destroy(*files);
	closedir(dirp);
	return (-1);
}

static int			ls_dir_content(t_dnarr **files, char *path)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_file			*tmp;

	if ((dirp = opendir(path)) == NULL)
		return (-1);
	*files = dnarr_create(sizeof(t_file), 50);
	while ((dp = readdir(dirp)) != NULL)
	{
		if (dp->d_name[0] == '.' && !(g_ls_opts & OPT_a || g_ls_opts & OPT_A))
			continue ;
		if (g_ls_opts & OPT_A && !(g_ls_opts & OPT_a) &&
				(!ft_strcmp(dp->d_name, ".") || !ft_strcmp(dp->d_name, "..")))
			continue ;
		tmp = dnarr_new(*files);
		ft_asprintf(&tmp->path, "%s/%s", path, dp->d_name);
		tmp->name = ft_strdup(dp->d_name);
		if (lstat(tmp->path, &(tmp->statbuf)) == -1)
			return (ls_free_dircont(tmp, files, dirp));
		dnarr_push(*files, tmp);
	}
	closedir(dirp);
	return (0);
}

static inline void	ls_recur(t_dnarr *files)
{
	int i;

	i = -1;
	while (++i < files->end)
	{
		if (S_ISDIR(((t_file *)files->contents[i])->statbuf.st_mode)
			&& !(ft_strcmp(((t_file *)files->contents[i])->name, ".") == 0
			|| ft_strcmp(((t_file *)files->contents[i])->name, "..") == 0))
		{
			ft_printf("\n%s:\n", ((t_file *)files->contents[i])->path);
			ls_print_dir(((t_file *)files->contents[i])->path);
		}
	}
}

int					ls_print_dir(char *path)
{
	t_dnarr	*files;
	int		i;

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
	ls_sort(files);
	if (g_ls_opts & OPT_l)
		ls_dir_l(files);
	else
		while (i < files->end)
			ft_printf("%s\n", ((t_file *)files->contents[i++])->name);
	if (g_ls_opts & OPT_R)
		ls_recur(files);
	ls_free_pn(files);
	dnarr_clrdestroy(files);
	return (0);
}
