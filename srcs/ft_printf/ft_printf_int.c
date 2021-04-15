/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:08:51 by jluknar-          #+#    #+#             */
/*   Updated: 2019/12/19 13:33:29 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*print_int(t_printer *printer, const char *types)
{
	int		i;
	char	*temp;

	i = va_arg(printer->arg, int);
	temp = ft_itoa(i);
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

void	widthonly_int(t_printer *printer, char *str, int i)
{
	int		spaces;

	if (printer->zeroflag && !printer->dotflag)
	{
		zeroes_int(printer, str, i);
		return ;
	}
	if (printer->width <= (int)ft_strlen(str))
	{
		ft_putstr(str);
		return ;
	}
	spaces = printer->width - (int)ft_strlen(str);
	while (spaces--)
	{
		ft_putchar(' ');
		printer->len++;
	}
	ft_putstr(str);
	return ;
}

void	zeroes_int(t_printer *printer, char *str, int i)
{
	int		spaces;

	if (i < 0)
	{
		i *= -1;
		str = ft_itoa(i);
		ft_putchar('-');
		i *= -1;
	}
	spaces = printer->width - (int)ft_strlen(str);
	i < 0 ? spaces-- : spaces;
	if (spaces < (int)ft_strlen(str))
	{
		ft_putstr(str);
		return ;
	}
	while (spaces--)
	{
		ft_putchar('0');
		printer->len++;
	}
	ft_putstr(str);
	if (i < 0)
		free(str);
	return ;
}

void	zeroes_int_prec(t_printer *printer, char *str, int i)
{
	int		spaces;

	if (printer->prec == 0 || printer->prec == -1)
		return ;
	if (i < 0)
	{
		i *= -1;
		str = ft_itoa(i);
		ft_putchar('-');
	}
	if (printer->prec <= (int)ft_strlen(str))
	{
		ft_putstr(str);
		return ;
	}
	spaces = printer->prec - (int)ft_strlen(str);
	i < 0 ? spaces-- : spaces;
	while (spaces--)
	{
		ft_putchar('0');
		printer->len++;
	}
	ft_putstr(str);
}
