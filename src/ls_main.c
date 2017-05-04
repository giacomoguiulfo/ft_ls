/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 14:58:56 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/05/03 22:50:19 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

long int g_ls_opts = 0;

int				ls_ftsopen(t_dnarr *dirs, t_dnarr *files, t_dnarr *naf)
{
	ft_dprintf(2, "ls: fts_open: No such file or directory\n");
	ls_free_pn(files);
	ls_free_pn(dirs);
	ls_handle_all(&naf, &files, &dirs, LS_KILL);
	return (-1);
}

static int		ls_parser(int argc, char **argv)
{
	int r;
	int i;

	i = 0;
	r = 0;
	while (++i < argc && argv[i][0] == '-' && ft_strcmp(argv[i], "-") && r == 0)
	{
		if ((r = ls_getopts(argv[i])) != -1)
			continue ;
		else
			return (-1);
	}
	if (i < argc)
	{
		if (ls_args(--i, argc, argv) == -1)
			return (-1);
	}
	else
	{
		if (g_ls_opts & OPT_d)
			return (ls_args(-1, 1, ft_strsplit(".", ' ')));
		if (ls_print_dir(".") == -1)
			return (-1);
	}
	return (0);
}

int				main(int argc, char **argv)
{
	if (argc == 1)
	{
		if (ls_print_dir(".") == -1)
			return (1);
	}
	else if (argc > 1)
	{
		if (ls_parser(argc, argv) == -1)
			return (1);
	}
	else
		return (1);
	return (0);
}
