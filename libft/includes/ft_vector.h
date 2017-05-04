/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 21:39:12 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/16 21:29:22 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

# include "libft.h"

typedef struct	s_cvector
{
	size_t		len;
	size_t		cap;
	char		*data;
}				t_cvector;

int				ft_cvector_init(t_cvector *vector, size_t init_cap);
void			ft_cvector_append(t_cvector *vector, char *newdata);
void			ft_cvector_resize(t_cvector *vector, size_t min);
void			ft_cvector_nappend(t_cvector *vector, char *newdata, size_t n);
void			ft_cvector_free(t_cvector *vector);

#endif
