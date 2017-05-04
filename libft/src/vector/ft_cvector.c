/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cvector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 23:35:03 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/16 00:12:33 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_vector.h>

int		ft_cvector_init(t_cvector *vector, size_t init_cap)
{
	if (!vector || !init_cap)
		return (-1);
	vector->len = 0;
	vector->cap = init_cap;
	if ((vector->data = ft_memalloc(sizeof(char) * vector->cap)) == NULL)
		return (-1);
	return (0);
}

void	ft_cvector_append(t_cvector *vector, char *newdata)
{
	size_t nd_len;

	nd_len = ft_strlen(newdata);
	if (vector->cap < vector->len + nd_len)
		ft_cvector_resize(vector, vector->len + nd_len);
	ft_memcpy(vector->data + vector->len, newdata, nd_len);
	vector->len += nd_len;
}

void	ft_cvector_resize(t_cvector *vector, size_t min)
{
	size_t	mllc_size;

	if (!(vector->data))
		ft_cvector_init(vector, min);
	mllc_size = vector->cap;
	while (mllc_size < min)
		mllc_size *= 2;
	vector->data = (char *)ft_recalloc(vector->data, vector->len, mllc_size);
	vector->cap = mllc_size;
}

void	ft_cvector_nappend(t_cvector *vector, char *newdata, size_t n)
{
	size_t nd_len;

	nd_len = n;
	if (vector->cap < vector->len + nd_len)
		ft_cvector_resize(vector, vector->len + nd_len);
	ft_memcpy(vector->data + vector->len, newdata, nd_len);
	vector->len += nd_len;
}

void	ft_cvector_free(t_cvector *vector)
{
	if (vector->data && vector->cap > 0)
	{
		free(vector->data);
		vector->data = NULL;
	}
}
