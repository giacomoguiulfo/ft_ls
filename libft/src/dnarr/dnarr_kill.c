/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dnarr_kill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 23:51:23 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/05/03 23:29:07 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dnarr.h>

void		dnarr_clr(t_dnarr *array)
{
	int i;

	i = 0;
	if (array->element_size > 0)
	{
		while (i < array->end)
		{
			if (array->contents[i] != NULL)
				free(array->contents[i]);
			++i;
		}
	}
}

void		dnarr_destroy(t_dnarr *array)
{
	if (array)
	{
		if (array->contents)
			free(array->contents);
		free(array);
	}
}

void		dnarr_clrdestroy(t_dnarr *array)
{
	dnarr_clr(array);
	dnarr_destroy(array);
}

void		*dnarr_remove(t_dnarr *array, int i)
{
	void *el;

	el = array->contents[i];
	array->contents[i] = NULL;
	return (el);
}
