/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:47:53 by jluknar-          #+#    #+#             */
/*   Updated: 2019/11/06 18:05:59 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	int		i;

	i = ft_strlen(s);
	ptr = (char*)s + i;
	if (c == '\0')
		return (ptr);
	if (c == '\0')
		return (ptr);
	while (i >= 0)
	{
		if (*ptr == c)
			return (ptr);
		ptr--;
		i--;
	}
	return (NULL);
}
