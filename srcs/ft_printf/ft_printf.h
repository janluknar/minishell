/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:36:21 by jluknar-          #+#    #+#             */
/*   Updated: 2019/12/19 13:14:14 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>
# include "libft/libft.h"

typedef	struct	s_printer
{
	va_list		arg;
	int			len;
	int			width;
	int			prec;
	char		set[10];
	int			dashflag;
	int			zeroflag;
	int			dotflag;
}				t_printer;

int				ft_printf(const char *types, ...);
char			*ft_itoa_base_hex(long long nbr, int base);
void			printer_init(t_printer *printer, const char *types);
void			printer_reset(t_printer *printer);
int				find_type(t_printer *printer, const char c);
char			*need_lines(t_printer *printer, char *types);
char			*need_lines_again(t_printer *printer, char *types);
char			*check_flags(t_printer *printer, char *types);
char			*case_caller(int case_type, t_printer *printer, char *types);
char			*print_char(t_printer *printer, char *types);
char			*print_str(t_printer *printer, const char *types);
char			*print_int(t_printer *printer, const char *types);
char			*print_unsigned(t_printer *printer, const char *types);
char			*print_addr(t_printer *printer, const char *types);
char			*print_hex(t_printer *printer,
		const char *types, int case_type);
char			*print_percentage(t_printer *printer, const char *types);
char			*prec_addr(t_printer *printer, char *str);
char			*zerostr(t_printer *printer, char *str);
char			*aux_negstr(t_printer *printer, char *str, int i);
char			*upper_hex(t_printer *printer, char *str,
		int case_type, unsigned int i);
void			dash(t_printer *printer, char *str);
void			widthonly(t_printer *printer, char *str);
void			widthonly_int(t_printer *printer, char *str, int i);
void			prec(t_printer *printer, char *str);
void			char_dash(t_printer *printer, char c);
void			dash_percentage(t_printer *printer, char per);
void			widthonly_percentage(t_printer *printer, char per);
void			zeroes_percentage(t_printer *printer, char per);
void			widthonly_addr(t_printer *printer, char *str);
void			dash_addr(t_printer *printer, char *str);
void			zeroes_int(t_printer *printer, char *str, int i);
void			zeroes_int_prec(t_printer *printer, char *str, int i);
void			width_prec_int(t_printer *printer, char *str, int i);
void			width_prec_dash(t_printer *printer, char *str, int i);
void			case1(t_printer *printer, char *str, int i);
void			case2(t_printer *printer, char *str, int i);
void			case2dash(t_printer *printer, char *str, int i);
void			int_dash(t_printer *printer, char *str);
#endif
