/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_auxiliary_int_functions.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 14:11:29 by jluknar-          #+#    #+#             */
/*   Updated: 2019/12/19 13:18:53 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	width_prec_int(t_printer *printer, char *str, int i)
{
	int	spaces;

	spaces = printer->width;
	if (printer->prec == -1 || printer->prec == 0)
	{
		while (spaces--)
		{
			ft_putchar(' ');
			printer->len++;
		}
		printer->len--;
		return ;
	}
	if (printer->prec <= ft_strlen(str))
		case1(printer, str, i);
	else if (printer->width <= printer->prec)
		zeroes_int_prec(printer, str, i);
	else
		case2(printer, str, i);
}

void	case1(t_printer *printer, char *str, int i)
{
	if (printer->dashflag)
	{
		if (printer->width > printer->prec && printer->prec > 0)
		{
			int_dash(printer, str);
			return ;
		}
		if (printer->width <= ft_strlen(str))
		{
			ft_putstr(str);
			return ;
		}
		dash(printer, str);
		return ;
	}
	if (printer->width <= ft_strlen(str))
	{
		ft_putstr(str);
		return ;
	}
	widthonly_int(printer, str, i);
}

void	case2(t_printer *printer, char *str, int i)
{
	int		spaces;
	int		zeroes;

	zeroes = printer->prec - ft_strlen(str);
	spaces = printer->width - printer->prec;
	printer->len += spaces + zeroes;
	if (i < 0)
	{
		spaces--;
		zeroes++;
		i *= -1;
		str = ft_itoa(i);
		i *= -1;
	}
	while (spaces--)
		ft_putchar(' ');
	if (i < 0)
		ft_putchar('-');
	while (zeroes--)
		ft_putchar('0');
	if (i < 0)
		free(str);
	ft_putstr(str);
}

void	width_prec_dash(t_printer *printer, char *str, int i)
{
	if (printer->width == -1 && !printer->dotflag)
		ft_putstr(str);
	if (printer->prec <= ft_strlen(str))
		case1(printer, str, i);
	else if (!printer->dotflag && printer->width > 0)
		dash(printer, str);
	else if (printer->width <= printer->prec)
		zeroes_int_prec(printer, str, i);
	else
		case2dash(printer, str, i);
}

void	case2dash(t_printer *printer, char *str, int i)
{
	int		spaces;
	int		zeroes;

	zeroes = printer->prec - ft_strlen(str);
	spaces = printer->width - printer->prec;
	printer->len += spaces + zeroes;
	if (i < 0)
	{
		spaces--;
		zeroes++;
		i *= -1;
		str = ft_itoa(i);
		i *= -1;
	}
	if (i < 0)
		ft_putchar('-');
	while (zeroes--)
		ft_putchar('0');
	if (i < 0)
		free(str);
	ft_putstr(str);
	while (spaces--)
		ft_putchar(' ');
}
