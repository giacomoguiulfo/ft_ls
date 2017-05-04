/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:16:57 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/15 19:42:24 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_printlst(t_list **head)
{
	t_list *node;

	node = *head;
	while (node)
	{
		ft_putstr((char *)node->content);
		ft_putchar('\n');
		node = node->next;
	}
}
