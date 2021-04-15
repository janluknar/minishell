/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 09:29:56 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/09 09:33:57 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strsub(const char *str, unsigned int start, size_t len)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (!str)
		return (NULL);
	if (!(tmp = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (len-- > 0 && str[i] != '\0')
		tmp[i++] = str[start++];
	tmp[i] = '\0';
	return (tmp);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (ret);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0 || (s1[i] == '\0' && s2[i] == '\0'))
		return (0);
	while ((unsigned char)s1[i] == (unsigned char)s2[i] && s1[i] && s2[i] &&
			n > i)
		i++;
	if (i == n)
		return (0);
	return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
}

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}
