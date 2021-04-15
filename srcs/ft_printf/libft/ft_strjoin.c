/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:42:22 by jluknar-          #+#    #+#             */
/*   Updated: 2019/11/13 15:39:29 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;

	if (!s2 || !s1)
		return (0);
	if (!(new = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char))))
		return (NULL);
	ft_memcpy(new, s1, ft_strlen(s1));
	i = 0;
	while (*s1)
	{
		new[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		new[i] = *s2;
		s2++;
		i++;
	}
	new[i] = '\0';
	return (new);
}
