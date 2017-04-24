/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 02:38:33 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/24 04:36:01 by gguiulfo         ###   ########.fr       */
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

int main(int argc, char **argv)
{
	if (argc != 2) return (0);
	/* Program */

	DIR *dir;
	DIR *inner;
	struct dirent *dp;
	t_btree *tree;

	dir = opendir(argv[1]);
	if (dir == NULL)
		return 1;
	tree = ft_btreenew(&(t_file){".", "."}, sizeof(t_file));
	while ((dp = readdir(dir)) != NULL)
	{
		if ((inner = (opendir(dp->d_name))) == NULL)
		{
			tree->right = ft_btreenew(&(t_file){".", "."}, sizeof(t_file))
		}
		ft_printf("%s and %s", FILENAME, FILEPATH);
		break ;
	}
	closedir(dir);
	return (0);
}
