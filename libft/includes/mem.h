/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 20:08:44 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/15 20:36:56 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H

void	ft_free_rows(void **d_arr, int rows);
void	*ft_memalloc(size_t size);
void	ft_memdel(void **ap);
void	*ft_recalloc(void *ptr, size_t src_size, size_t new_size);
void	ft_swap(void *a, void *b, size_t s);

#endif
