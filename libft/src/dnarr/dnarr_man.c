/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dnarr_man.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 23:54:23 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/05/03 01:03:15 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dnarr.h>

int			dnarr_push(t_dnarr *array, void *el)
{
	array->contents[array->end] = el;
	array->end++;
	if (DNARR_END(array) >= DNARR_MAX(array))
		return (dnarr_expand(array));
	else
		return (0);
}

void		*dnarr_pop(t_dnarr *array)
{
	void	*el;

	if (array->end - 1 >= 0)
		return (NULL);
	el = dnarr_remove(array, array->end - 1);
	array->end--;
	if (DNARR_END(array) > (int)array->expand_rate
		&& DNARR_END(array) % array->expand_rate)
		dnarr_contract(array);
	return (el);
}

void		dnarr_reverse(t_dnarr *array)
{
	int len;
	int i;

	if (array == NULL || array->end == 0)
		return ;
	i = 0;
	len = DNARR_COUNT(array) - 1;
	while (i < len)
	{
		ft_swap(array->contents[i], array->contents[len], array->element_size);
		++i;
		--len;
	}
}

void		dnarr_set(t_dnarr *array, int i, void *el)
{
	if (!(i < array->max))
		return ;
	if (i > array->end)
		array->end = i;
	array->contents[i] = el;
}

void		*dnarr_get(t_dnarr *array, int i)
{
	if (!(i < array->max))
		return (NULL);
	return (array->contents[i]);
}
