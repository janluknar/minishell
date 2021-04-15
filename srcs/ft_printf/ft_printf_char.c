/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:20:53 by jluknar-          #+#    #+#             */
/*   Updated: 2019/12/19 13:20:26 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*print_char(t_printer *printer, char *types)
{
	char	c;
	int		spaces;

	c = va_arg(printer->arg, int);
	if (printer->dashflag == 0 && printer->width > 0)
	{
		spaces = printer->width - 1;
		while (spaces--)
		{
			printer->len++;
			ft_putchar(' ');
		}
	}
	if (printer->dashflag)
		char_dash(printer, c);
	else
		ft_putchar(c);
	printer->len++;
	types++;
	return ((char *)types);
}
