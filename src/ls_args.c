/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 09:01:18 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/30 06:06:09 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

extern int g_ls_opts;

void	ls_naf_handle(t_dnarr *naf)
{
	int i;

	i = 0;
	while (i < naf->end)
	{
		ft_qsort(naf->contents, 0, dnarr_count(naf) - 1, (t_sortcast) ft_strcmp);
		while (i < naf->end)
			ft_dprintf(2, "ft_ls: %s: %s\n", (char *)naf->contents[i++], strerror(errno)); // TODO: Instead of ls it could be argv[0]
	}
	i = -1;
	while (++i < naf->end)
	{
		;// free(naf->contents[0]);
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
	i = 0;
	if (i < files->end)
		ft_ls_sort(files);
	if (g_ls_opts & OPT_l)
	{
		while (i < files->end)
		{
			ls_file_l((t_file *)files->contents[i], padding, ((t_file *)files->contents[i])->path);
			i++;
		}
	}
	else
	{
		while (i < files->end)
			ft_printf("%s\n", ((t_file *)files->contents[i++])->path);
	}
	i = -1;
	while (++i < files->end)
	{
		free(((t_file *)files->contents[i])->path);
		free(((t_file *)files->contents[i])->name);
	}
}

void	ls_dirs_handle(t_dnarr *dirs, t_dnarr *files)
{
	int i;

	i = 0;
	if (i < dirs->end)
	{
		ft_ls_sort(dirs);
		while (i < dirs->end)
		{
			if (!(((t_file *)dirs->contents[i])->path[0] == '/')) // TODO: Check this
			// if (!(((t_file *)dirs->contents[j])->path[0] == '/') && dirs->end > 1) // TODO: Check this
				ft_printf("%s%s:\n", (files->end > 0 || i) ? "\n" : "", ((t_file *)dirs->contents[i])->path);
			ls_print_dir(((t_file *)dirs->contents[i++])->path);
		}
	}
	i = -1;
	while (++i < dirs->end)
	{
		free(((t_file *)dirs->contents[i])->path);
		free(((t_file *)dirs->contents[i])->name);
	}
}

void	ls_handle_all(t_dnarr **naf, t_dnarr **files, t_dnarr **dirs, int action)
{
	if (action == 0)
	{
		*naf = dnarr_create(sizeof(char *), 10);
		*dirs = dnarr_create(sizeof(t_file), 25);
		*files = dnarr_create(sizeof(t_file), 50);
	}
	else if (action == 1)
	{
		if ((*naf)->end > 0)
			ls_naf_handle(*naf);
		if ((*files)->end > 0)
			ls_file_handle(*files);
		if ((*dirs)->end > 0)
			ls_dirs_handle(*dirs, *files); // TODO: Change files to files->end
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

	// naf = dnarr_create(sizeof(char *), 10);
	// dirs = dnarr_create(sizeof(t_file), 25);
	// files = dnarr_create(sizeof(t_file), 50);
	ls_handle_all(&naf, &files, &dirs, 0);
	while (i < argc)
	{
		tmp = dnarr_new(dirs);
		if (lstat(argv[i], &tmp->statbuf) == -1)
		{
			dnarr_push(naf, ft_strdup(argv[i++]));
			free(tmp);
			continue ;
		}
		tmp->name = ft_strdup(ls_pathname(argv[i])); // I dont need dups
		tmp->path = ft_strdup(argv[i]); // I dont need dups
		// if (S_ISDIR(tmp->statbuf.st_mode))
		// if ((dir = opendir(tmp->path)) != NULL)
		if (stat(argv[i], &tmp->statbuf) != 1 && S_ISDIR(tmp->statbuf.st_mode))
		{
			// closedir(dir);
			dnarr_push(dirs, tmp);
		}
		else
		{
			dnarr_push(files, tmp);
		}
		i++;
	}

	ls_handle_all(&naf, &files, &dirs, 1);
	ls_handle_all(&naf, &files, &dirs, 2);
	// ls_naf_handle(naf);
	// ls_file_handle(files);
	// ls_dirs_handle(dirs, files);
	// TODO: free all this function...
	return (0);
}
