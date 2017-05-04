/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_opts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:36:48 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/05/03 21:40:51 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

extern long int g_ls_opts;

static int			ls_usage(char flag)
{
	ft_dprintf(2, "ls: illegal option -- %c\n", flag);
	ft_dprintf(2, "usage: ft_ls [-ARSTacdfgolrt1] [file ...]\n");
	return (-1);
}

static inline void	ls_time_opts(char chr)
{
	if (chr == 'c')
	{
		if (g_ls_opts & OPT_u)
			g_ls_opts ^= OPT_u;
		if (g_ls_opts & OPT_U)
			g_ls_opts ^= OPT_U;
		g_ls_opts |= OPT_c;
	}
	else if (chr == 'u')
	{
		if (g_ls_opts & OPT_c)
			g_ls_opts ^= OPT_c;
		if (g_ls_opts & OPT_U)
			g_ls_opts ^= OPT_U;
		g_ls_opts |= OPT_u;
	}
	else
	{
		if (g_ls_opts & OPT_c)
			g_ls_opts ^= OPT_c;
		if (g_ls_opts & OPT_u)
			g_ls_opts ^= OPT_u;
		g_ls_opts |= OPT_U;
	}
}

static inline int	ls_moar_opts(char chr)
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

static inline int	ls_more_opts(char chr)
{
	if (chr == 'd')
		g_ls_opts |= OPT_d;
	else if (chr == 'S')
		g_ls_opts |= OPT_S;
	else if (chr == 'T')
		g_ls_opts |= OPT_T;
	else if (chr == 'A')
		g_ls_opts |= OPT_A;
	else if (chr == 'u' || chr == 'U' || chr == 'c')
		ls_time_opts(chr);
	else
		return (ls_moar_opts(chr));
	return (0);
}

int					ls_getopts(char *str)
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
