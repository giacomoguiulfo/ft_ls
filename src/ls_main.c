/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 14:58:56 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/26 06:44:02 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

#include <stdio.h> // Dont forget to delete

typedef int (*comps) (const void *a, const void *b);
//
// static void swap(void *x, void *y, size_t l) {
//    char *a = x, *b = y, c;
//    while(l--) {
//       c = *a;
//       *a++ = *b;
//       *b++ = c;
//    }
// }
//
// static void sort(char *array, size_t size, int (*cmp)(const void*, const void*), int begin, int end) {
//    if (end > begin) {
//       void *pivot = array + begin;
//       int l = begin + size;
//       int r = end;
//       while(l < r) {
//          if (cmp(array+l,pivot) <= 0) {
//             l += size;
//          } else if ( cmp(array+r, pivot) > 0 )  {
//             r -= size;
//          } else if ( l < r ) {
//             swap(array+l, array+r, size);
//          }
//       }
//       l -= size;
//       swap(array+begin, array+l, size);
//       sort(array, size, cmp, begin, l);
//       sort(array, size, cmp, r, end);
//    }
// }
//
// void ft_qsort(void *array, size_t nitems, size_t size, int (*cmp)(const void*, const void*)) {
//    sort(array, size, cmp, 0, nitems*size);
// }

void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void myqsort(void *v[], int left, int right, int (*comp)(const void *, const void *)) {
	int i, last;

	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	i = left + 1;
	while (i <= right)
	{
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
		++i;
	}
	swap(v, left, last);
	myqsort(v, left, last-1, comp);
	myqsort(v, last+1, right, comp);
}

// void myqsort(void *v, int left, int right, int (*comp)(const void *, const void *)) {
// 	int i, last;
//
// 	if (left >= right)
// 		return;
// 	swap(v, left, (left + right)/2);
// 	last = left;
// 	i = left + 1;
// 	while (i <= right)
// 	{
// 		if ((*comp)(v[i], v[left]) < 0)
// 			swap(v, ++last, i);
// 		++i;
// 	}
// 	swap(v, left, last);
// 	myqsort(v, left, last-1, comp);
// 	myqsort(v, last+1, right, comp);
// }

int		ft_perror(const char *s)
{
	ft_dprintf(2, "%{red}%s%s\n%{eoc}", s, strerror(errno));
	return (-1);
}

int		cmpfunc(void *a, void *b)
{
	char *str1;
	char *str2;

	str1 = ((t_file *)(a))->name;
	str2 = ((t_file *)(b))->name;
	return (strcmp(str1, str2));
}

// void	ft_bubblesort(void *array, size_t size, int end, int (*comp)(const void *, const void *))
// {
// 	int i;
// 	int j;
//
// 	i = 0;
// 	while (i < end)
// 	{
// 		j = 0;
// 		while (j < end - 1)
// 		{
// 			if (comp(&array[j], &array[j + 1]))
// 			{
// 				ft_swap(&array[j], &array[j + 1], size);
// 			}
// 			++j;
// 		}
// 		++i;
// 	}
// }



// int		cmpfunc(char **a, char **b)
// {
// 	char *str1;
// 	char *str2;
//
// 	str1 = ((t_file *)(*a))->name;
// 	str2 = ((t_file *)(*b))->name;
// 	return (strcmp(str1, str2));
// }


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
	*files = dnarr_create(sizeof(t_file), 100); // TODO: t_file or t_file *
	while ((dp = readdir(dirp)) != NULL)
	{
		if (dp->d_name[0] == '.')
			continue ;
		tmp = dnarr_new(*files);
		ft_asprintf(&tmp->path, "%s/%s", path, dp->d_name);
		tmp->name = ft_strdup(dp->d_name);
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
	// ft_printf("Debug: %s\n", );
	// ft_bubblesort(files->contents, sizeof(void *), dnarr_count(files) - 1, (comps) cmpfunc);
	// qsort(files->contents, dnarr_count(files), sizeof(void *), (comps) cmpfunc);
	// ft_qsort(files->contents, dnarr_count(files) - 1, sizeof(void *), (comps) cmpfunc);
	myqsort(files->contents, 0, dnarr_count(files) - 1, (comps) cmpfunc);
	while (i < files->end)
		ft_printf("%s\n", ((t_file *)files->contents[i++])->name);
	if (recursive)
	{
		i = 0;
		while (i < files->end)
		{
			// printf("%s\n", "hello");
			// ft_printf("Current Name: %s\n", ((t_file *)files->contents[i])->name);;
			// ft_printf("Current Path: %s\n", ((t_file *)files->contents[i])->path);;
			// printf("Is dir? %d\n", ft_isdir(((t_file *)files->contents[i])->statbuf.st_mode));
			// ft_printf("Is dir? %d\n", ((t_file *)files->contents[i])->statbuf.st_mode);
			// ft_printf("Is dir? %d\n", S_ISDIR(((t_file *)files->contents[i])->statbuf.st_mode));

			if (S_ISDIR(((t_file *)files->contents[i])->statbuf.st_mode)
				&& !(ft_strcmp(((t_file *)files->contents[i])->name, ".") == 0
				|| ft_strcmp(((t_file *)files->contents[i])->name, "..") == 0))
			{
				// ft_printf("%s\n", "hello");
				ft_printf("\n%s:\n", ((t_file *)files->contents[i])->path);
				ls_print_dir(((t_file *)files->contents[i])->path);
			}
			++i;
		}
	}
	i = 0;
	// while (i < files->end)
		// free(((t_file *)files->contents[i++])->path);
	// TODO: Make another one of this ones for ->name
	// dnarr_clrdestroy(files);
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
