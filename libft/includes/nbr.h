/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 20:12:38 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/15 20:25:28 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NBR_H
# define NBR_H

char		*ft_imaxtoa(intmax_t value);
int			ft_is_sort(int *tab, int length, int (*f)(int, int));
char		*ft_itoa_base(int value, int base);
char		*ft_itoa(int n);
long long	ft_nblen(long long nb);
void		ft_putnbr_fd(int n, int fd);
void		ft_putnbr(int n);
int			*ft_range(int min, int max);
char		*ft_uimaxtoa_base(uintmax_t value, int8_t base, const char *str);

#endif
