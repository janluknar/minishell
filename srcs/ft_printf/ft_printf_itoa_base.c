/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_itoa_base.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:35:26 by jluknar-          #+#    #+#             */
/*   Updated: 2019/12/18 15:37:40 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	*ft_memalloc(size_t size)
{
	void	*mem;

	mem = malloc(size);
	if (mem == NULL)
		return (NULL);
	ft_memset(mem, 0, size);
	return (mem);
}

static char	set(int nbr)
{
	if (nbr >= 10)
		return ('a' - 10 + nbr);
	else if (nbr < 0)
		return (-nbr + '0');
	else
		return (nbr + '0');
}

static int	numlen(long long nbr, int base)
{
	int	len;

	len = 0;
	if (!nbr)
		return (2);
	while (nbr)
	{
		nbr /= base;
		len++;
	}
	return (len);
}

char		*ft_itoa_base_hex(long long nbr, int base)
{
	char		*str;
	long long	stand;
	int			x;

	x = numlen(nbr, base) - 1;
	str = ft_memalloc(x + 2);
	if (!nbr)
		str[0] = '0';
	stand = nbr;
	if (nbr < 0)
		stand = nbr * -1;
	while (stand)
	{
		str[x] = set(stand % base);
		stand /= base;
		x--;
	}
	return (str);
}
