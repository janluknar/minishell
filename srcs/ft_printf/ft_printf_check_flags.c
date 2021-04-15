/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_check_flags.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 14:42:22 by jluknar-          #+#    #+#             */
/*   Updated: 2019/12/19 13:22:03 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		isdatatype(char c)
{
	if (c == 'c' || c == 's' || c == 'p'
			|| c == 'd' || c == 'i' || c == 'u'
			|| c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

char	*check_flags(t_printer *printer, char *types)
{
	while (!isdatatype(*types))
	{
		while (*types == '-' || *types == '0')
		{
			if (*types == '-')
				printer->dashflag = 1;
			if (*types == '0')
				printer->zeroflag = 1;
			types++;
		}
		types = need_lines_again(printer, types);
		if (*types++ == '.' && (printer->prec++))
			types = need_lines(printer, types);
		else
		{
			types--;
			return (types);
		}
	}
	return (types);
}

char	*need_lines(t_printer *printer, char *types)
{
	printer->dotflag = 1;
	if (*types == '*')
	{
		printer->prec = va_arg(printer->arg, int);
		if (printer->prec < 0)
		{
			printer->dotflag = 0;
			printer->prec = -1;
		}
		types++;
	}
	else
	{
		while (ft_isdigit(*types))
			printer->prec = printer->prec * 10 + (*types++ - '0');
	}
	return (types);
}

char	*need_lines_again(t_printer *printer, char *types)
{
	if (*types == '*')
	{
		printer->width = va_arg(printer->arg, int);
		if (printer->width < 0)
		{
			printer->dashflag = 1;
			printer->width *= -1;
		}
		types++;
	}
	else
	{
		while (ft_isdigit(*types))
		{
			if (printer->width == -1)
				printer->width++;
			printer->width = printer->width * 10 + (*types - '0');
			types++;
		}
	}
	return (types);
}
