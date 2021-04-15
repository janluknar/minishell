/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 09:26:07 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/09 09:29:27 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t		ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char		*ft_strdup(const char *str)
{
	char	*tmp;
	size_t	i;

	if (!str)
		return (NULL);
	if (!(tmp = (char *)malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (NULL);
	i = 0;
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

void		ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (((str[i] == '"' || str[i] == '\'') && i == 0)
		|| ((str[i] == '"' || str[i] == '\'') && i == ft_strlen(str) - 1))
			i++;
		else
		{
			ft_putchar(str[i]);
			i++;
		}
	}
}

char		*ft_strjoin(const char *s1, const char *s2)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	j = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(tmp = (char *)malloc(sizeof(char) * j)))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j] != '\0')
		tmp[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		tmp[i++] = s2[j++];
	tmp[i] = '\0';
	return (tmp);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char*)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}
