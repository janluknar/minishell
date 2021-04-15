/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_addr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 17:44:55 by jluknar-          #+#    #+#             */
/*   Updated: 2019/12/19 13:17:23 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*print_addr(t_printer *printer, const char *types)
{
	unsigned long	i;
	char			*temp;

	i = va_arg(printer->arg, unsigned long);
	temp = ft_itoa_base_hex((long long)i, 16);
	if (printer->dotflag && !printer->dashflag)
		temp = prec_addr(printer, temp);
	temp = ft_strjoin("0x", temp);
	if (printer->dotflag && printer->width == -1 && !printer->dashflag)
		ft_putstr(temp);
	if (printer->dashflag)
		dash_addr(printer, temp);
	if (!printer->dashflag && printer->width > 0)
		widthonly_addr(printer, temp);
	if (!printer->dashflag && printer->width == -1 && printer->prec == -1)
		ft_putstr(temp);
	printer->len += ft_strlen(temp);
	types++;
	free(temp);
	return ((char *)types);
}

void	dash_addr(t_printer *printer, char *str)
{
	int		spaces;

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

void	widthonly_addr(t_printer *printer, char *str)
{
	int		spaces;

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

char	*prec_addr(t_printer *printer, char *str)
{
	if (printer->prec == -1 || printer->prec == 0)
	{
		str[0] = '\0';
		return (str);
	}
	if (printer->prec <= ft_strlen(str))
	{
		str[printer->prec + 1] = '\0';
		return (str);
	}
	if (printer->prec > 0 && printer->prec > ft_strlen(str))
		str = zerostr(printer, str);
	return (str);
}

char	*zerostr(t_printer *printer, char *str)
{
	int		zeroes;
	int		i;
	char	*temp;

	i = 0;
	zeroes = ft_strlen(str);
	temp = (char *)malloc(((printer->prec - zeroes) + 1 * sizeof(char)));
	while (zeroes++ < printer->prec)
		temp[i++] = '0';
	str = ft_strjoin(temp, str);
	free(temp);
	return (str);
}
