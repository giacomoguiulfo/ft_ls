/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_str_conv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 17:33:03 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/16 00:12:03 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_helpers.h>

char	*ft_null_str(t_info *pfinfo)
{
	char *temp;

	if (pfinfo->prec >= 1 || pfinfo->prec == -1)
	{
		temp = ft_strdup("(null)");
		if (pfinfo->prec > 6)
			temp[6] = '\0';
		else
			temp[(pfinfo->prec == -1) ? 6 : pfinfo->prec] = '\0';
	}
	else
		temp = ft_strdup("");
	return (temp);
}

void	ft_str_conv(t_cvector *vector, t_info *pfinfo, va_list ap)
{
	char *ctemp;
	char *str;

	if (pfinfo->length == l)
	{
		ft_wstr_conv(vector, pfinfo, ap);
		return ;
	}
	ctemp = va_arg(ap, char *);
	if (!ctemp)
		str = ft_null_str(pfinfo);
	else
		str = ft_strdup(ctemp);
	ft_prec_handle(pfinfo, &str);
	ft_pad_handle(pfinfo, &str);
	ft_cvector_append(vector, str);
	free(str);
}
