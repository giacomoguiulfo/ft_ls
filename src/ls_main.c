/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 14:58:56 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/30 03:53:20 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

#include <stdio.h> // Dont forget to delete

int g_ls_opts = 0;

int		ft_perror(const char *s)
{
	// ft_dprintf(2, "%{red}%s%s\n%{eoc}", s, strerror(errno));
	ft_dprintf(2, "%s%s\n", s, strerror(errno));
	return (-1);
}

int		ls_usage(char flag)
{
	ft_printf("ls: illegal option -- %c\n", flag);
	ft_printf("usage: ls [-Ralrt] [file ...]\n");
	return (-1);
}

int		ls_getopts(char *str)
{
	int i;

	i = 0;
	if (!ft_strcmp(str, "--"))
		return (0);
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
		else if (str[i] == '1')
			;
		else
			return (ls_usage(str[i]));
	}
	return (0);
}

int		ls_parser(int argc, char **argv)
{
	int i;

	i = 0;
	while (++i < argc && argv[i][0] == '-')
	{
		if (ls_getopts(argv[i]) == 0)
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
