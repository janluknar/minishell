/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 12:40:01 by jluknar-          #+#    #+#             */
/*   Updated: 2020/09/09 09:40:45 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	ft_l(void)
{
	size_t	lmts;

	lmts = (size_t)(9223372036854775807 / 10);
	return (lmts);
}

int				ft_atoi(const char *s)
{
	int				sign;
	unsigned long	r;

	r = 0;
	sign = 1;
	while (*s == 32 || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	else if (*s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		if ((r > ft_l() || (r == ft_l() && (*s - '0') > 7)) && sign == 1)
			return (-1);
		else if ((r > ft_l() || (r == ft_l() && (*s - '0') > 8)) && sign == -1)
			return (0);
		r = r * 10 + *s - '0';
		s++;
	}
	return (sign * (int)r);
}

static	void	itoa_isnegative(int *n, int *negative)
{
	if (*n < 0)
	{
		*n *= -1;
		*negative = 1;
	}
}

char			*ft_itoa(int n)
{
	int		tmpn;
	int		len;
	int		negative;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	tmpn = n;
	len = 2;
	negative = 0;
	itoa_isnegative(&n, &negative);
	while (tmpn /= 10)
		len++;
	len += negative;
	if ((str = (char*)malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	str[--len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
	}
	if (negative)
		str[0] = '-';
	return (str);
}

void			ft_free_array2d(char **str, int len)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (i < len)
	{
		if (str[i] != NULL)
			free(str[i]);
		str[i++] = NULL;
	}
	if (str != NULL)
		free(str);
	str = NULL;
}
