/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:22:35 by jluknar-          #+#    #+#             */
/*   Updated: 2019/12/19 13:40:26 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_itoa_unsigned(unsigned int nbr)
{
	long	n;
	size_t	len;
	char	*str;

	n = nbr;
	len = (n > 0) ? 0 : 1;
	n = (n > 0) ? n : -n;
	while (nbr)
		nbr = len++ ? nbr / 10 : nbr / 10;
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	*(str + len--) = '\0';
	while (n > 0)
	{
		*(str + len--) = n % 10 + '0';
		n /= 10;
	}
	if (len == 0 && str[1] == '\0')
		*(str + len) = '0';
	if (len == 0 && str[1] != '\0')
		*(str + len) = '-';
	return (str);
}

char		*print_unsigned(t_printer *printer, const char *types)
{
	unsigned int	i;
	char			*temp;

	i = va_arg(printer->arg, unsigned int);
	if (i < 0)
		i = 4294967295 + i;
	temp = ft_itoa_unsigned(i);
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
