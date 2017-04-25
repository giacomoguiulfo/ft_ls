/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 14:58:56 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/25 08:03:00 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

#include <stdio.h> // Dont forget to delete

int		ft_perror(const char *s)
{
	ft_dprintf(2, "%{red}%s%s\n%{eoc}", s, strerror(errno));
	return (-1);
}

int	ft_isdir(mode_t mode)
{
	int			bits;

	bits = (mode & S_IFMT);
	if (bits == S_IFDIR)
		return (1);
	return (0);
}

int		ls_dir_content(t_dnarr **files, char *path)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_file			*tmp;
	
	if ((dirp = opendir(path)) == NULL)
		return (-1);
	*files = dnarr_create(sizeof(t_file), 50); // TODO: t_file or t_file *
	while ((dp = readdir(dirp)) != NULL)
	{
		if (dp->d_name[0] == '.')
			continue ;
		tmp = dnarr_new(*files);
		ft_asprintf(&tmp->path, "%s/%s", path, dp->d_name);
		tmp->name = dp->d_name;
		if (lstat(tmp->path, &(tmp->statbuf)) == -1)
		{
			free(tmp->path);
			dnarr_destroy(*files);
			closedir(dirp);
			return (-1);
		}
		dnarr_push(*files, tmp);
		// free(tmp->path);
	}
	closedir(dirp);
	return (0);
}

int recursive = 1;

int		ls_print_dir(char *path)
{
	t_dnarr *files;
	int i;

	i = 0;
	if (ls_dir_content(&files, path) == -1)
	{
		ft_dprintf(2, "ls: %s: %s\n", "path", strerror(errno));
		return (-1);
	}
	if (files->end == 0)
	{
		dnarr_clrdestroy(files);
		return (-1);
	}
	while (i < files->end)
		ft_printf("%s\n", ((t_file *)files->contents[i++])->name);
	if (recursive)
	{
		i = 0;
		while (i < files->end)
		{
			// printf("%s\n", "hello");
			// printf("Current Name: %s\n", ((t_file *)files->contents[i])->name);;
			// printf("Current Path: %s\n", ((t_file *)files->contents[i])->path);;
			// printf("Is dir? %d\n", ft_isdir(((t_file *)files->contents[i])->statbuf.st_mode));
			// printf("%d\n", ((t_file *)files->contents[i])->statbuf.st_mode);
			// printf("%d\n", S_ISDIR(((t_file *)files->contents[i])->statbuf.st_mode));
			// exit(1);
			if (S_ISDIR(((t_file *)files->contents[i])->statbuf.st_mode)
				&& !(ft_strcmp(((t_file *)files->contents[i])->name, ".") == 0
				|| ft_strcmp(((t_file *)files->contents[i])->name, "..") == 0))
			{
				// printf("%s\n", "hello");
				printf("\n%s:\n", ((t_file *)files->contents[i])->path);
				ls_print_dir(((t_file *)files->contents[i])->path);
			}
			++i;
		}
	}
	i = 0;
	while (i < files->end)
		free(((t_file *)files->contents[i++])->path);
	dnarr_clrdestroy(files);
	return (0);
}

int		main(int argc, char **argv)
{
	if (argc == 1)
	{
		if (ls_print_dir(".") == -1)
			return (-1);
	}
	else if (argc > 1)
		(void)argv;
	else
		return (-1);
	return (0);
}
