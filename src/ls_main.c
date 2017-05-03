/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 14:58:56 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/05/03 06:01:47 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

long int g_ls_opts = 0;

int		ls_usage(char flag)
{
	ft_dprintf(2, "ls: illegal option -- %c\n", flag);
	ft_dprintf(2, "usage: ft_ls [-Ralrt] [file ...]\n");
	return (-1);
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
		else if (str[i] == 'S')
			g_ls_opts |= OPT_S;
		else if (str[i] == 'T')
			g_ls_opts |= OPT_T;
		else if (str[i] == 'A')
			g_ls_opts |= OPT_A;
		else if (str[i] == 'd')
			g_ls_opts |= OPT_d;
		else if (str[i] == 'f')
		{
			g_ls_opts |= OPT_a;
			g_ls_opts |= OPT_f;
		}
		else if (str[i] == 'o')
		{
			g_ls_opts |= OPT_l;
			g_ls_opts |= OPT_o;
		}
		else if (str[i] == 'g')
		{
			g_ls_opts |= OPT_l;
			g_ls_opts |= OPT_g;
		}
		else if (str[i] == '1')
		{
			if (g_ls_opts & OPT_l)
				g_ls_opts ^= OPT_l;
		}
		else
			return (ls_usage(str[i]));
	}
	return (0);
}

int		ls_parser(int argc, char **argv)
{
	int ret;
	int i;

	i = 0;
	ret = 0;
	while (++i < argc && argv[i][0] == '-' && ft_strcmp(argv[i], "-") &&
			ret == 0)
	{
		if ((ret = ls_getopts(argv[i])) != -1)
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
