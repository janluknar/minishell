/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 13:11:58 by jluknar-          #+#    #+#             */
/*   Updated: 2019/12/19 13:12:45 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *types, ...)
{
	t_printer	*printer;

	if (!(printer = (t_printer *)malloc(sizeof(t_printer))))
		return (0);
	printer_init(printer, types);
	va_start(printer->arg, types);
	while (*types)
	{
		if (*types == '%')
		{
			types++;
			types = check_flags(printer, (char *)types);
			types = case_caller(find_type(printer, *types),
					printer, (char *)types);
		}
		else
		{
			ft_putchar(*types);
			types++;
			printer->len++;
		}
	}
	va_end(printer->arg);
	free(printer);
	return (printer->len);
}
