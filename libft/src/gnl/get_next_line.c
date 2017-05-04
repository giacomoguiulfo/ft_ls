/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 21:44:34 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/15 21:03:36 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static t_list	*ft_getnode(t_list **lst, int fd)
{
	t_list	*tempnode;

	tempnode = *lst;
	while (tempnode)
	{
		if (tempnode->content_size == (size_t)fd)
			return (tempnode);
		tempnode = tempnode->next;
	}
	ft_lstadd(lst, ft_lstnew("\0", sizeof(char)));
	(*lst)->content_size = fd;
	return ((*lst));
}

static int		ft_setline(t_list **tempnode, char **line, size_t size)
{
	*line = ft_strndup(((*tempnode)->content), size);
	ft_memmove((*tempnode)->content, (*tempnode)->content + size + 1,
											ft_strlen((*tempnode)->content));
	return (1);
}

static int		ft_lastline(t_list **node, char **line)
{
	size_t extra_len;

	extra_len = ft_strlen((*node)->content);
	*line = ft_strdup((*node)->content);
	ft_bzero((*node)->content, extra_len);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static	t_list	*node = NULL;
	t_list			*temp;
	char			buf[GNL_BUFF_SIZE + 1];
	int				ret;
	char			*ctmp;

	if (fd < 0 || read(fd, buf, 0) < 0 || !line)
		return (-1);
	temp = ft_getnode(&node, fd);
	while ((ret = read(fd, buf, GNL_BUFF_SIZE)))
	{
		buf[ret] = '\0';
		ctmp = temp->content;
		temp->content = ft_strjoin(temp->content, buf);
		free(ctmp);
		if ((ctmp = ft_strchr(temp->content, '\n')) != NULL)
			return (ft_setline(&temp, line, ctmp - (char *)temp->content));
	}
	if ((ctmp = ft_strchr(temp->content, '\n')) != NULL)
		return (ft_setline(&temp, line, ctmp - (char *)temp->content));
	else if (ft_strlen(temp->content) > 0)
		return (ft_lastline(&temp, line));
	ft_lstdelnode(&node, temp);
	return (0);
}
