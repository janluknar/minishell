/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_widthonly.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:28:16 by jluknar-          #+#    #+#             */
/*   Updated: 2019/12/19 13:41:03 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	widthonly(t_printer *printer, char *str)
{
	int		spaces;

	if (printer->dotflag == 1)
	{
		if (printer->prec == -1 || printer->prec == 0)
			str[0] = '\0';
		if (printer->prec <= ft_strlen(str))
			str[printer->prec] = '\0';
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
}
