/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 09:01:18 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/05/03 06:05:32 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

extern long int g_ls_opts;

void	ls_naf_handle(t_dnarr *naf)
{
	int i;

	i = 0;
	while (i < naf->end)
	{
		ft_qsort(naf->contents, 0, DNARR_COUNT(naf) - 1, (t_sortcast)ft_strcmp);
		while (i < naf->end)
			ft_dprintf(2, "ls: %s: %s\n", (char *)naf->contents[i++],
															strerror(errno));
	}
}

void	ls_file_handle(t_dnarr *files)
{
	int i;
	int padding[4];

	i = 0;
	ft_bzero(padding, sizeof(int) * 4);
	while (i < files->end)
		ls_padding_l(padding, ((t_file *)files->contents[i++])->statbuf);
	i = -1;
	if (files->end > 0)
		ft_ls_sort(files);
	if (g_ls_opts & OPT_l)
		while (++i < files->end)
			ls_file_l((t_file *)files->contents[i], padding,
						((t_file *)files->contents[i])->path);
	else
		while (++i < files->end)
			ft_printf("%s\n", ((t_file *)files->contents[i])->path);
	ls_free_pn(files);
}

void	ls_dirs_handle(t_dnarr *dirs, int f_end, int naf_end)
{
	int i;

	i = 0;
	if (i < dirs->end)
	{
		ft_ls_sort(dirs);
		while (i < dirs->end)
		{
			if (/*!(((t_file *)dirs->contents[i])->path[0] == '/') &&*/
					(dirs->end > 1 || f_end > 0 || naf_end > 0))
				ft_printf("%s%s:\n", (f_end > 0 || i) ? "\n" : "",
							((t_file *)dirs->contents[i])->path);
			ls_print_dir(((t_file *)dirs->contents[i])->path);
			free(((t_file *)dirs->contents[i])->path);
			free(((t_file *)dirs->contents[i])->name);
			++i;
		}
	}
}

void	ls_handle_all(t_dnarr **naf, t_dnarr **files, t_dnarr **dirs, int act)
{
	if (act == 0)
	{
		*naf = dnarr_create(sizeof(char *), 10);
		*dirs = dnarr_create(sizeof(t_file), 25);
		*files = dnarr_create(sizeof(t_file), 50);
	}
	else if (act == 1)
	{
		if ((*naf)->end > 0)
			ls_naf_handle(*naf);
		if ((*files)->end > 0)
			ls_file_handle(*files);
		if ((*dirs)->end > 0)
			ls_dirs_handle(*dirs, (*files)->end, (*naf)->end);
	}
	else
	{
		dnarr_clrdestroy(*naf);
		dnarr_clrdestroy(*files);
		dnarr_clrdestroy(*dirs);
	}
}

int		ls_args(int i, int argc, char **argv)
{
	t_dnarr *dirs;
	t_dnarr *files;
	t_dnarr *naf;
	t_file	*tmp;

	ls_handle_all(&naf, &files, &dirs, 0);
	while (i < argc)
	{
		if (argv[i][0] == 0)
		{
			ft_dprintf(2, "ls: fts_open: No such file or directory\n");
			ls_free_pn(files);
			ls_free_pn(dirs);
			ls_handle_all(&naf, &files, &dirs, 2);
			return (-1);
		}
		tmp = dnarr_new(dirs);
		if (lstat(argv[i], &tmp->statbuf) == -1)
		{
			dnarr_push(naf, ft_strdup(argv[i++]));
			free(tmp);
			continue ;
		}
		tmp->name = ft_strdup(ls_pathname(argv[i]));
		tmp->path = ft_strdup(argv[i]);
		if (!(S_ISLNK(tmp->statbuf.st_mode) && (g_ls_opts & OPT_l)) &&
			stat(argv[i], &tmp->statbuf) != 1 && S_ISDIR(tmp->statbuf.st_mode) && !(g_ls_opts & OPT_d))
			dnarr_push(dirs, tmp);
		else
			dnarr_push(files, tmp);
		i++;
	}
	if (g_ls_opts & OPT_d && argc == 1)
		ft_free_map(argv);
	ls_handle_all(&naf, &files, &dirs, 1);
	ls_handle_all(&naf, &files, &dirs, 2);
	return (0);
}
