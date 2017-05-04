/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:07:22 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/15 20:10:01 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memalloc(size_t size)
{
	void			*mem;
	unsigned char	*str;

	if (size == 0 || (mem = malloc(size)) == 0)
		return (0);
	str = (unsigned char *)mem;
	while (size--)
		*str++ = 0;
	return (mem);
}
