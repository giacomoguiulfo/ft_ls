/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_more.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 03:56:39 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/25 06:23:27 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_helpers.h>

int		ft_asprintf(char **ret, const char *format, ...)
{
	va_list ap;
	int		len;

	if (!format || !*format)
		return (0);
	va_start(ap, format);
	len = ft_vasprintf(ret, format, ap);
	if (len < 0)
		return (-1);
	va_end(ap);
	return (len);
}
