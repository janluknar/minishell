/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_dash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 14:19:55 by jluknar-          #+#    #+#             */
/*   Updated: 2019/12/19 13:24:21 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	dash(t_printer *printer, char *str)
{
	int		spaces;

	if (printer->dotflag == 1)
	{
		if (printer->prec == -1 || printer->prec == 0)
			str[0] = '\0';
		if (printer->prec <= ft_strlen(str))
			str[printer->prec] = '\0';
		if (printer->width == -1)
			return ;
	}
	if (printer->width <= (int)ft_strlen(str))
	{
		ft_putstr(str);
		return ;
	}
	spaces = printer->width - (int)ft_strlen(str);
	ft_putstr(str);
	while (spaces--)
	{
		ft_putchar(' ');
		printer->len++;
	}
}

void	prec(t_printer *printer, char *str)
{
	if (printer->prec == -1 || printer->prec == 0)
	{
		str[0] = '\0';
		return ;
	}
	if (printer->prec <= ft_strlen(str))
	{
		str[printer->prec] = '\0';
		ft_putstr(str);
		return ;
	}
	if (printer->prec > 0 && printer->prec > ft_strlen(str))
		ft_putstr(str);
}

void	char_dash(t_printer *printer, char c)
{
	int	spaces;

	ft_putchar(c);
	if (printer->width == -1)
		return ;
	spaces = printer->width - 1;
	while (spaces--)
	{
		ft_putchar(' ');
		printer->len++;
	}
}

void	int_dash(t_printer *printer, char *str)
{
	int	spaces;

	spaces = printer->width - (int)ft_strlen(str);
	ft_putstr(str);
	while (spaces--)
	{
		ft_putchar(' ');
		printer->len++;
	}
}
