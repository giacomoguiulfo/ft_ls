/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctype.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 19:06:17 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/16 00:16:01 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CTYPE_H
# define FT_CTYPE_H

# define ISALPHA(a) (((unsigned)a | 32) - 97 < 26u)
# define ISASCII(a) ((unsigned)a < 128u)
# define ISDIGIT(a) (((unsigned)a-48) < 10u)
# define ISALNUM(a) (ISALPHA(a) || ISDIGIT(a))
# define ISPRINT(a) (((unsigned)a - 32) < 95u)
# define ISSPACE(a) ((a >= 9 && a <= 13) || (a == 32))
# define TOLOWER(a) (((unsigned)a - 65) < 26u ? a + 32 : a)
# define TOUPPER(a) (((unsigned)a - 97) < 26u ? a - 32 : a)

int	ft_isalnum(int c);
int	ft_isalpha(int c);
int	ft_isascii(int c);
int	ft_isdigit(int c);
int	ft_isprint(int c);
int ft_isspace(int c);
int	ft_tolower(int c);
int	ft_toupper(int c);

#endif
