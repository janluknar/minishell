/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 09:39:15 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/09 09:43:35 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_strrtrim(char *str)
{
	size_t	i;

	if (!str)
		return ;
	i = ft_strlen(str) - 1;
	while ((i) && (str[i] == ' ' || str[i] == ';'))
		str[i--] = 0;
	if (str[i] == ' ' || str[i] == ';')
		str[i] = 0;
}

void	ft_next_quote(char *line, char c, int *pi)
{
	int	i;

	i = *pi;
	if (c == '"')
	{
		i++;
		while (line[i] != '"' && line[i] != '\0')
			i++;
	}
	else if (c == '\'')
	{
		i++;
		while (line[i] != '\'' && line[i] != '\0')
			i++;
	}
	i++;
	*pi = i;
}

void	ft_rtrim(char *str, char c)
{
	size_t	i;

	i = ft_strlen(str) - 1;
	while (str[i] == c && i >= 0)
		str[i--] = 0;
}

char	*ft_strstr(char *hstk, const char *ndl)
{
	size_t i;
	size_t j;

	if (*ndl == '\0')
		return ((char*)hstk);
	i = 0;
	while (hstk[i])
	{
		j = 0;
		while (hstk[i + j] == ndl[j] && ndl[j])
		{
			j++;
			if (ndl[j] == '\0')
				return ((char*)hstk + i);
		}
		i++;
	}
	return (NULL);
}

int		ft_isnum(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
