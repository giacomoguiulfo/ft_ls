/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 09:01:18 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/30 01:28:00 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

extern int g_ls_opts;

int		ls_args(int i, int argc, char **argv)
{
	// DIR *dir;
	t_dnarr *dirs;
	t_dnarr *files;
	t_dnarr *naf;
	t_file	*tmp;

	int j;
	naf = dnarr_create(sizeof(char *), 10);
	dirs = dnarr_create(sizeof(t_file), 25);
	files = dnarr_create(sizeof(t_file), 50);
	while (i < argc)
	{
		// if (ls_dir_content(&files, argv[i]) == -1)
		// {
		// 	// ft_dprintf(2, "ls: %s: %s\n", ls_pathname(argv[i]), strerror(errno));
		// 	ft_printf("%s\n", argv[i]);
		// 	continue ;
		// }
		// ft_printf("%s\n", argv[i]);
		tmp = dnarr_new(dirs);
		if (lstat(argv[i], &tmp->statbuf) == -1)
		{
			dnarr_push(naf, ft_strdup(argv[i++]));
			// ft_dprintf(2, "ls: %s: %s\n", argv[i++], strerror(errno));
			continue ;
		}
		// ft_printf("---------lala---------\n");
		//
		// ft_printf("---------lala---------argv[i]: %s\n", argv[i]);
		tmp->name = ft_strdup(ls_pathname(argv[i])); // I dont need dups
		tmp->path = ft_strdup(argv[i]); // I dont need dups
		// ft_printf("tmp->path: [%s]\n", tmp->path);
		// ft_printf("tmp->name: [%s]\n", tmp->name);
		// if (S_ISDIR(tmp->statbuf.st_mode))
		// if ((dir = opendir(tmp->path)) != NULL)
		if (stat(argv[i], &tmp->statbuf) != 1 && S_ISDIR(tmp->statbuf.st_mode))
		{
			// closedir(dir);
			// ft_printf("---------gfds---------[%s]\n", argv[i]);
			dnarr_push(dirs, tmp);
		}
		else
		{
			// ft_printf("---------chic---------[%s]\n", argv[i]);
			if (tmp->path && tmp->path[0])
				dnarr_push(files, tmp->path);
		}
		i++;
	}

	j = 0;
	if (j < naf->end)
	{
		ft_qsort(naf->contents, 0, dnarr_count(naf) - 1, (t_sortcast) ft_strcmp);
		while (j < naf->end)
			ft_dprintf(2, "ls: %s: %s\n", (char *)naf->contents[j++], strerror(errno)); // TODO: Instead of ls it could be argv[0]
	}
	j = 0;
	if (j < files->end)
	{
		ft_qsort(files->contents, 0, dnarr_count(files) - 1, (t_sortcast) ft_strcmp);
		while (j < files->end)
		{
			// if (g_ls_opts & OPT_l)
				// handle file function -> that covers long formatting/ padding/ etc // TODO: do this...
			// else
				ft_printf("%s\n", (char *)files->contents[j++]);
		}
	}
	j = 0;
	if (j < dirs->end)
	{
		ft_qsort(dirs->contents, 0, dnarr_count(dirs) - 1, (t_sortcast) cmpfunc);
		// ft_printf("%s\n", "---------------------here");
		while (j < dirs->end)
		{
			if (!(((t_file *)dirs->contents[j])->path[0] == '/')) // TODO: Check this
			// if (!(((t_file *)dirs->contents[j])->path[0] == '/') && dirs->end > 1) // TODO: Check this
				ft_printf("%s%s:\n", (files->end > 0 || j) ? "\n" : "", ((t_file *)dirs->contents[j])->path);
			ls_print_dir(((t_file *)dirs->contents[j++])->path);
		}
	// // 		ft_dprintf(2, "ls: %s: %s\n", (char *)dirs->contents[j++], strerror(errno));
	}
	// TODO: free all this function...
	// while (j < files->end)
	// 	ft_printf("%s\n", ((t_file *)files->contents[j++])->name);
	return (0);
}
