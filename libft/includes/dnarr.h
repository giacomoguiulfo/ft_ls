/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dnarr.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 01:30:18 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/05/03 01:04:44 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DNARR_H
# define DNARR_H

# include "libft.h"

# define DEFAULT_EXPAND_RATE 300
# define DNARR_LAST(a) ((a)->contents[(a)->end - 1])
# define DNARR_FIRST(a) ((a)->contents[0])
# define DNARR_END(a) ((a)->end)
# define DNARR_COUNT(a) DNARR_END(a)
# define DNARR_MAX(a) ((a)->max)

typedef int	(*t_sortcast) (const void *a, const void *b);

typedef	struct		s_dnarr
{
	int				end;
	int				max;
	size_t			element_size;
	size_t			expand_rate;
	void			**contents;
}					t_dnarr;

t_dnarr				*dnarr_create(size_t element_size, size_t initial_max);
void				dnarr_clr(t_dnarr *array);
int					dnarr_expand(t_dnarr *array);
int					dnarr_contract(t_dnarr *array);
void				dnarr_destroy(t_dnarr *array);
void				dnarr_clrdestroy(t_dnarr *array);
int					dnarr_push(t_dnarr *array, void *el);
void				*dnarr_pop(t_dnarr *array);
void				dnarr_reverse(t_dnarr *array);
void				*dnarr_remove(t_dnarr *array, int i);
void				*dnarr_new(t_dnarr *array);
void				dnarr_set(t_dnarr *array, int i, void *el);
void				*dnarr_get(t_dnarr *array, int i);

#endif
