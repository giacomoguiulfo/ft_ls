/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 13:44:32 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/15 20:00:42 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d_str;
	unsigned const char	*s_str;
	unsigned char		chr;

	d_str = (unsigned char *)dst;
	s_str = (unsigned const char *)src;
	chr = (unsigned char)c;
	while (n--)
		if ((*d_str++ = *s_str++) == chr)
			return ((void *)d_str);
	return (NULL);
}
