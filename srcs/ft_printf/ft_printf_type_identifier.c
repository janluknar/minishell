/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_type_identifier.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 10:01:16 by jluknar-          #+#    #+#             */
/*   Updated: 2019/12/19 13:39:06 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printer_init(t_printer *printer, const char *types)
{
	printer->len = 0;
	printer->prec = -1;
	printer->width = -1;
	printer->set[0] = 'c';
	printer->set[1] = 's';
	printer->set[2] = 'p';
	printer->set[3] = 'd';
	printer->set[4] = 'i';
	printer->set[5] = 'u';
	printer->set[6] = 'x';
	printer->set[7] = 'X';
	printer->set[8] = '%';
	printer->set[9] = '\0';
	printer->dashflag = 0;
	printer->zeroflag = 0;
	printer->dotflag = 0;
}

void	printer_reset(t_printer *printer)
{
	printer->prec = -1;
	printer->width = -1;
	printer->dashflag = 0;
	printer->zeroflag = 0;
	printer->dotflag = 0;
}

int		find_type(t_printer *printer, const char c)
{
	int i;

	i = 0;
	while (i < 10)
	{
		if (printer->set[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
