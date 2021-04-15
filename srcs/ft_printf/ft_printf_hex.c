/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 12:11:41 by jluknar-          #+#    #+#             */
/*   Updated: 2019/12/19 13:30:53 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*to_upper(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] + ('A' - 'a');
		i++;
	}
	return (str);
}

char	*print_hex(t_printer *printer, const char *types, int case_type)
{
	char			*temp;
	unsigned int	i;

	i = va_arg(printer->arg, unsigned int);
	if (i < 0)
		i = 4294967295 + i;
	temp = upper_hex(printer, temp, case_type, i);
	if (printer->dotflag && printer->width == -1)
		zeroes_int_prec(printer, temp, i);
	if (printer->dashflag)
		width_prec_dash(printer, temp, i);
	if (printer->dotflag && printer->width > 0 && !printer->dashflag)
		width_prec_int(printer, temp, i);
	if (!printer->dashflag && printer->width > 0 && !printer->dotflag)
		widthonly_int(printer, temp, i);
	if (!printer->dashflag && !printer->dotflag && printer->width == -1)
		ft_putstr(temp);
	if (printer->dotflag && (printer->prec == 0 || printer->prec == -1)
			&& printer->width == -1)
		printer->len--;
	printer->len += ft_strlen(temp);
	types++;
	free(temp);
	return ((char *)types);
}

char	*upper_hex(t_printer *printer, char *str, int case_type, unsigned int i)
{
	if (case_type == 6)
		str = ft_itoa_base_hex((long long)i, 16);
	else
	{
		str = ft_itoa_base_hex((long long)i, 16);
		str = to_upper(str);
	}
	return (str);
}
