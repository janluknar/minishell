/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_percentage.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:17:52 by jluknar-          #+#    #+#             */
/*   Updated: 2019/12/19 13:35:50 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*print_percentage(t_printer *printer, const char *types)
{
	if (printer->dashflag)
		dash_percentage(printer, '%');
	if (!printer->dashflag && printer->width > 0 && !printer->zeroflag)
		widthonly_percentage(printer, '%');
	if (printer->zeroflag && !printer->dashflag)
		zeroes_percentage(printer, '%');
	if (!printer->dashflag && printer->width == -1 && printer->prec == -1)
		ft_putchar('%');
	printer->len++;
	types++;
	return ((char *)types);
}

void	dash_percentage(t_printer *printer, char per)
{
	int		spaces;

	if (printer->width <= 1)
	{
		ft_putchar(per);
		return ;
	}
	spaces = printer->width - 1;
	ft_putchar(per);
	while (spaces--)
	{
		ft_putchar(' ');
		printer->len++;
	}
}

void	widthonly_percentage(t_printer *printer, char per)
{
	int		spaces;

	if (printer->width <= 1)
	{
		ft_putchar(per);
		return ;
	}
	spaces = printer->width - 1;
	while (spaces--)
	{
		ft_putchar(' ');
		printer->len++;
	}
	ft_putchar(per);
}

void	zeroes_percentage(t_printer *printer, char per)
{
	int		spaces;

	if (printer->width <= 1)
	{
		ft_putchar(per);
		return ;
	}
	spaces = printer->width - 1;
	while (spaces--)
	{
		ft_putchar('0');
		printer->len++;
	}
	ft_putchar(per);
}
