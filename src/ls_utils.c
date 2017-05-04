/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:47:05 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/05/03 22:41:52 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ls_free_pn(t_dnarr *files)
{
	int i;

	i = -1;
	while (++i < files->end)
	{
		free(((t_file *)files->contents[i])->path);
		free(((t_file *)files->contents[i])->name);
	}
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

void	ls_padding_l(int *padding, struct stat statbuf)
{
	padding[0] = MAX(padding[0], ft_nblen(statbuf.st_nlink));
	padding[1] = MAX(padding[1],
							(int)ft_strlen(getpwuid(statbuf.st_uid)->pw_name));
	padding[2] = MAX(padding[2],
							(int)ft_strlen(getgrgid(statbuf.st_gid)->gr_name));
	padding[3] = MAX(padding[3], ft_nblen(statbuf.st_size));
}

void	ls_print_link(char *path)
{
	char linkname[PATH_MAX + 1];

	ft_bzero(linkname, PATH_MAX + 1);
	readlink(path, linkname, PATH_MAX);
	ft_putstr(" -> ");
	ft_putstr(linkname);
}

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
