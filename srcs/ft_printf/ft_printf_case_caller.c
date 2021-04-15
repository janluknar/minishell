/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_case_caller.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:24:30 by jluknar-          #+#    #+#             */
/*   Updated: 2019/12/19 13:19:46 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*case_caller(int case_type, t_printer *printer, char *types)
{
	if (case_type == 0)
		types = print_char(printer, types);
	if (case_type == 1)
		types = print_str(printer, types);
	if (case_type == 2)
		types = print_addr(printer, types);
	if (case_type == 3 || case_type == 4)
		types = print_int(printer, types);
	if (case_type == 5)
		types = print_unsigned(printer, types);
	if (case_type == 6 || case_type == 7)
		types = print_hex(printer, types, case_type);
	if (case_type == 8)
		types = print_percentage(printer, types);
	printer_reset(printer);
	return (types);
}
