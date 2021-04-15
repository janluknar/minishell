/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:43:25 by jluknar-          #+#    #+#             */
/*   Updated: 2019/12/19 13:36:56 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*print_str(t_printer *printer, const char *types)
{
	char	*temp;

	temp = va_arg(printer->arg, char *);
	if (!temp)
		temp = ft_strdup("(null)");
	temp = ft_strdup(temp);
	if ((printer->dotflag == 1 && printer->width == -1))
		prec(printer, temp);
	if (printer->dashflag == 1)
		dash(printer, temp);
	if (printer->dashflag == 0 && printer->width > 0)
		widthonly(printer, temp);
	if (!printer->dashflag && printer->width == -1 && printer->prec == -1)
		ft_putstr(temp);
	printer->len += ft_strlen(temp);
	types++;
	free(temp);
	return ((char *)types);
}
