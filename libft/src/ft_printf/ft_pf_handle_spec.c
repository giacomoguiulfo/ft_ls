/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_handle_spec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 23:28:43 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/16 00:12:07 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_helpers.h>

t_convtbl g_convtbl[] =
{
	{'d', &ft_num_conv},
	{'D', &ft_num_conv},
	{'i', &ft_num_conv},
	{'p', &ft_hex_conv},
	{'o', &ft_octal_conv},
	{'O', &ft_octal_conv},
	{'x', &ft_hex_conv},
	{'X', &ft_hex_conv},
	{'u', &ft_uns_conv},
	{'U', &ft_uns_conv},
	{'s', &ft_str_conv},
	{'S', &ft_wstr_conv},
	{'c', &ft_chr_conv},
	{'C', &ft_chr_conv},
	{'b', &ft_binary_conv},
	{'f', &ft_float_conv},
	{'n', &ft_none_conv},
	{'%', &ft_pct_conv}
};

void	ft_get_conv(t_cvector *vector, t_info *pfinfo, va_list ap)
{
	int i;

	i = -1;
	while (++i < SPECTOTAL)
	{
		if (pfinfo->spec == g_convtbl[i].spec)
		{
			g_convtbl[i].f(vector, pfinfo, ap);
			return ;
		}
	}
	ft_pct_conv(vector, pfinfo, ap);
}

void	ft_handle_spec(t_cvector *vector, const char **format,
													t_info *pfinfo, va_list ap)
{
	if (**format == '{')
		if (ft_pfcolors(vector, format) == true)
			return ;
	while (1)
	{
		if (ft_chk_flags(format, pfinfo))
			continue ;
		if (ft_chk_width(format, pfinfo, ap))
			continue ;
		if (ft_chk_prec(format, pfinfo, ap))
			continue ;
		if (ft_chk_len(format, pfinfo))
			continue ;
		if (**format == '\0')
			return ;
		pfinfo->spec = *(*format)++;
		break ;
	}
	ft_get_conv(vector, pfinfo, ap);
}

int		ft_strprintf(char **ret, const char *format, va_list ap)
{
	size_t		i;
	t_cvector	vector;
	t_info		pfinfo;

	ft_pfinfo_init(&pfinfo);
	if (ft_cvector_init(&vector, ft_strlen(format) + 50) == FAILED)
		return (FAILED);
	while (*format)
	{
		i = 0;
		while (format[i] && format[i] != '%')
			i++;
		ft_cvector_nappend(&vector, (char *)format, i);
		format += i;
		if (*format == '%')
		{
			if (*(++format) == 0)
				break ;
			ft_handle_spec(&vector, &format, &pfinfo, ap);
		}
		ft_pfinfo_init(&pfinfo);
	}
	*ret = ft_strndup(vector.data, vector.len);
	ft_cvector_free(&vector);
	return (vector.len);
}

void	ft_pfinfo_init(t_info *pfinfo)
{
	pfinfo->width = 0;
	pfinfo->prec = -1;
	pfinfo->spec = 'N';
	pfinfo->flags = 0;
	pfinfo->length = -1;
	pfinfo->pset = 0;
}

void	ft_pct_conv(t_cvector *vector, t_info *pfinfo, va_list ap)
{
	char *str;

	(void)ap;
	str = ft_strnew(1);
	*str = pfinfo->spec;
	ft_pad_handle(pfinfo, &str);
	ft_cvector_append(vector, str);
	free(str);
}
