/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 14:58:56 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/05/03 06:49:20 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

long int g_ls_opts = 0;

int		ls_usage(char flag)
{
	ft_dprintf(2, "ls: illegal option -- %c\n", flag);
	ft_dprintf(2, "usage: ft_ls [-ARSTacdfgolrt1] [file ...]\n");
	return (-1);
}

int		ls_moar_opts(char chr)
{
	if (chr == 'f')
	{
		g_ls_opts |= OPT_a;
		g_ls_opts |= OPT_f;
	}
	else if (chr == 'o')
	{
		g_ls_opts |= OPT_l;
		g_ls_opts |= OPT_o;
	}
	else if (chr == 'g')
	{
		g_ls_opts |= OPT_l;
		g_ls_opts |= OPT_g;
	}
	else if (chr == '1')
	{
		if (g_ls_opts & OPT_l)
			g_ls_opts ^= OPT_l;
	}
	else
		return (ls_usage(chr));
	return (0);
}

int		ls_more_opts(char chr)
{
	if (chr == 'c')
		g_ls_opts |= OPT_c;
	else if (chr == 'd')
		g_ls_opts |= OPT_d;
	else if (chr == 'S')
		g_ls_opts |= OPT_S;
	else if (chr == 'T')
		g_ls_opts |= OPT_T;
	else if (chr == 'A')
		g_ls_opts |= OPT_A;
	else
		return (ls_moar_opts(chr));
	return (0);
}

int		ls_getopts(char *str)
{
	int i;

	i = 0;
	if (!ft_strcmp(str, "--"))
		return (1);
	while (str[++i])
	{
		if (str[i] == 'l')
			g_ls_opts |= OPT_l;
		else if (str[i] == 'R')
			g_ls_opts |= OPT_R;
		else if (str[i] == 'a')
			g_ls_opts |= OPT_a;
		else if (str[i] == 'r')
			g_ls_opts |= OPT_r;
		else if (str[i] == 't')
			g_ls_opts |= OPT_t;
		else
		{
			if (ls_more_opts(str[i]) != 0)
				return (-1);
		}
	}
	return (0);
}

int		ls_parser(int argc, char **argv)
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
		if (ls_args(i, argc, argv) == -1)
			return (-1);
	}
	else
	{
		if (g_ls_opts & OPT_d)
			return (ls_args(0, 1, ft_strsplit(".", ' ')));
		if (ls_print_dir(".") == -1)
			return (-1);
	}
	return (0);
}

int		main(int argc, char **argv)
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
