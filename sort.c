/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 02:38:33 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/24 06:14:56 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

#define FILENAME (((t_file *)tree->content)->name)
#define FILEPATH (((t_file *)tree->content)->path)

typedef struct		s_file
{
	char *path;
	char *name;
}					t_file;

typedef struct		s_btree
{
	void			*content;
	size_t			content_size;
	struct	s_btree	*left;
	struct	s_btree	*right;
}					t_btree;

t_btree	*ft_btreenew(void const *content, size_t content_size)
{
	t_btree	*node;

	if ((node = (t_btree *)malloc(sizeof(t_btree))) == NULL)
		return (NULL);
	if (!content)
	{
		node->content = NULL;
		node->content_size = 0;
	}
	else
	{
		if ((node->content = malloc(sizeof(content_size))) == NULL)
		{
			free(node);
			return (NULL);
		}
		ft_memcpy(node->content, content, content_size);
		node->content_size = content_size;
	}
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int	ft_isdir(const char *s)
{
	struct stat	statbuf;
	int			bits;

	lstat(s, &statbuf);
	bits = (statbuf.st_mode & S_IFMT);
	if (bits == S_IFDIR)
		return (1);
	return (0);
}

void	ft_btree_isrtdata(t_btree **root, void *item)
{
	DIR *dir;
	struct dirent *dp;
	char *name;
	char *path;

	name = ((t_file)(*root)->content)->name);
	path = ((t_file)(*root)->content)->path);
	if (ft_isdir(path))
	{
		(*root)->right = ft_btreenew(&(t_file){name, path}, sizeof(t_file));
		dir = opendir(path);
		dp = readdir(dir);
		ft_btree_isrtdata(&(*root)->right, dp.d_name);
	}
	else
	{
		(*root)->left = ft_btreenew(&(t_file){name, path}, sizeof(t_file));
		ft_btree_isrtdata(&(*root)->right, dp.d_name);
	}
}

void	ft_print_btree(t_btree *tree)
{
	ft_printf("Hello\n");
	if (tree)
	{
		ft_printf("Content: %s\n", FILENAME);
		ft_print_btree(tree->left);
		ft_print_btree(tree->right);
	}
}

int main(int argc, char **argv)
{
	if (argc != 2) return (0);
	/* Program */

	DIR *dir;
	struct dirent *dp;
	t_btree *tree;
	t_btree *initial;

	dir = opendir(argv[1]);
	if (dir == NULL)
		return 1;
	tree = ft_btreenew(&(t_file){".", "."}, sizeof(t_file));
	initial = tree;
	while ((dp = readdir(dir)) != NULL)
	{
		ft_btree_isrtdata(&(tree->left), dp->d_name);
		ft_printf("%s\n", dp->d_name);
		// ft_printf("%s and %s", FILENAME, FILEPATH);
		// break ;
	}
	ft_print_btree(initial);
	closedir(dir);
	return (0);
}
