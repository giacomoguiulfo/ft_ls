/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_multi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 05:46:06 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/05/03 21:01:32 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

extern long int g_ls_opts;

int		ls_lexcmp(void *a, void *b)
{
	return (ft_strcmp(((t_file *)(a))->path, ((t_file *)(b))->path));
}

// int		ls_timecmp(void *a, void *b)
// {
// 	long diff;
// 	long ndiff;
//
// 	diff = ((t_file *)(b))->statbuf.st_mtimespec.tv_sec -
// 			((t_file *)(a))->statbuf.st_mtimespec.tv_sec;
// 	if (diff == 0)
// 	{
// 		ndiff = ((t_file *)(b))->statbuf.st_mtimespec.tv_nsec -
// 				((t_file *)(a))->statbuf.st_mtimespec.tv_nsec;
// 		if (ndiff == 0)
// 			return (ft_strcmp(((t_file *)(a))->path, ((t_file *)(b))->path));
// 		return (ndiff);
// 	}
// 	return (diff);
// }
//
// int		ls_ctimecmp(void *a, void *b)
// {
// 	long diff;
// 	long ndiff;
//
// 	diff = ((t_file *)(b))->statbuf.st_ctimespec.tv_sec -
// 			((t_file *)(a))->statbuf.st_ctimespec.tv_sec;
// 	if (diff == 0)
// 	{
// 		ndiff = ((t_file *)(b))->statbuf.st_ctimespec.tv_nsec -
// 				((t_file *)(a))->statbuf.st_ctimespec.tv_nsec;
// 		if (ndiff == 0)
// 			return (ft_strcmp(((t_file *)(a))->path, ((t_file *)(b))->path));
// 		return (ndiff);
// 	}
// 	return (diff);
// }
//
// int		ls_atimecmp(void *a, void *b)
// {
// 	long diff;
// 	long ndiff;
//
// 	diff = ((t_file *)(b))->statbuf.st_atimespec.tv_sec -
// 			((t_file *)(a))->statbuf.st_atimespec.tv_sec;
// 	if (diff == 0)
// 	{
// 		ndiff = ((t_file *)(b))->statbuf.st_atimespec.tv_nsec -
// 				((t_file *)(a))->statbuf.st_atimespec.tv_nsec;
// 		if (ndiff == 0)
// 			return (ft_strcmp(((t_file *)(a))->path, ((t_file *)(b))->path));
// 		return (ndiff);
// 	}
// 	return (diff);
// }
//
// int		ls_btimecmp(void *a, void *b)
// {
// 	long diff;
// 	long ndiff;
//
// 	diff = ((t_file *)(b))->statbuf.st_birthtimespec.tv_sec -
// 			((t_file *)(a))->statbuf.st_birthtimespec.tv_sec;
// 	if (diff == 0)
// 	{
// 		ndiff = ((t_file *)(b))->statbuf.st_birthtimespec.tv_nsec -
// 				((t_file *)(a))->statbuf.st_birthtimespec.tv_nsec;
// 		if (ndiff == 0)
// 			return (ft_strcmp(((t_file *)(a))->path, ((t_file *)(b))->path));
// 		return (ndiff);
// 	}
// 	return (diff);
// }

void	ls_get_timefmt(void *a, void *b)
{
	if (g_ls_opts & OPT_c)
	{
		((t_file *)(a))->cmptime = ((t_file *)(a))->statbuf.st_ctimespec;
		((t_file *)(b))->cmptime = ((t_file *)(b))->statbuf.st_ctimespec;
	}
	else if (g_ls_opts & OPT_U)
	{
		((t_file *)(a))->cmptime = ((t_file *)(a))->statbuf.st_birthtimespec;
		((t_file *)(b))->cmptime = ((t_file *)(b))->statbuf.st_birthtimespec;
	}
	else if (g_ls_opts & OPT_u)
	{
		((t_file *)(a))->cmptime = ((t_file *)(a))->statbuf.st_atimespec;
		((t_file *)(b))->cmptime = ((t_file *)(b))->statbuf.st_atimespec;
	}
	else
	{
		((t_file *)(a))->cmptime = ((t_file *)(a))->statbuf.st_mtimespec;
		((t_file *)(b))->cmptime = ((t_file *)(b))->statbuf.st_mtimespec;
	}
}

int		ls_tmcmp(void *a, void *b)
{
	long diff;
	long ndiff;

	ls_get_timefmt(a, b);
	diff = ((t_file *)(b))->cmptime.tv_sec  - ((t_file *)(a))->cmptime.tv_sec;
	if (!diff)
	{
		ndiff = ((t_file *)(b))->cmptime.tv_nsec  - ((t_file *)(a))->cmptime.tv_nsec;
		if (!ndiff)
			return (ft_strcmp(((t_file *)(a))->path, ((t_file *)(b))->path));
		return (ndiff);
	}
	return (diff);
}

int		ls_sizecmp(void *a, void *b)
{
	if (!(((t_file *)(b))->statbuf.st_size - ((t_file *)(a))->statbuf.st_size))
		return (ft_strcmp(((t_file *)(a))->path, ((t_file *)(b))->path));
	return (((t_file *)(b))->statbuf.st_size -
			((t_file *)(a))->statbuf.st_size);
}

void	ft_ls_sort(t_dnarr *files)
{
	if (g_ls_opts & OPT_f)
		return ;
	if (g_ls_opts & OPT_S)
		ft_qsort(files->contents, 0, DNARR_COUNT(files) - 1,
													(t_sortcast)ls_sizecmp);
	else if (g_ls_opts & OPT_t)
	{
		ft_qsort(files->contents, 0, DNARR_COUNT(files) - 1, (t_sortcast)ls_tmcmp);
	// 	if (g_ls_opts & OPT_c)
	// 		ft_qsort(files->contents, 0, DNARR_COUNT(files) - 1,
	// 												(t_sortcast)ls_ctimecmp);
	// 	else if (g_ls_opts & OPT_U)
	// 		ft_qsort(files->contents, 0, DNARR_COUNT(files) - 1,
	// 												(t_sortcast)ls_btimecmp);
	// 	else
	// 		ft_qsort(files->contents, 0, DNARR_COUNT(files) - 1,
	// 	(g_ls_opts & OPT_u) ? (t_sortcast)ls_atimecmp : (t_sortcast)ls_timecmp);
	}
	else
		ft_qsort(files->contents, 0, DNARR_COUNT(files) - 1,
													(t_sortcast)ls_lexcmp);
	if (g_ls_opts & OPT_r)
		dnarr_reverse(files);
}
