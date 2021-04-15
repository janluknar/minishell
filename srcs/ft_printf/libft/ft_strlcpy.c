/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 09:24:32 by jluknar-          #+#    #+#             */
/*   Updated: 2019/11/13 11:20:56 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	count;

	if (!src)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	count = 0;
	while (dstsize > 1 && *src)
	{
		*dst = *src;
		++dst;
		++src;
		--dstsize;
		++count;
	}
	*dst = '\0';
	while (*dst || *src)
	{
		if (*src)
		{
			++src;
			++count;
		}
	}
	return (count);
}
