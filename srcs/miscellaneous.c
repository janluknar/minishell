/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <jluknar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 12:46:30 by jluknar-          #+#    #+#             */
/*   Updated: 2020/09/09 09:45:31 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_count_scolon(t_shell *sh)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	if (!sh->line)
		return (ret);
	while (++i < ft_strlen(sh->line))
	{
		if (sh->line[i] == '"' || sh->line[i] == '\'')
			ft_next_quote(sh->line, sh->line[i], &i);
		if (sh->line[i] == ';')
			ret++;
	}
	return (ret);
}

int		ft_del_space(char *str, int *pi)
{
	int	i;

	i = *pi;
	while (str[i] == ' ' && str[i] != '\0')
		i++;
	*pi = i;
	return (i);
}

void	ft_del_scape(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = ft_strdup(str);
	i = 0;
	j = 0;
	while (i < ft_strlen(tmp))
	{
		if (tmp[i] == '\\' && (tmp[i + 1] == '"' || tmp[i + 1] == '\''))
		{
			i++;
			str[j] = tmp[i];
			j++;
			i++;
		}
		else
			str[j++] = tmp[i++];
	}
	str[j] = 0;
	free(tmp);
	tmp = NULL;
}

void	ft_del_quotes_aux(char *str, char *tmp, int *j, int *i)
{
	if (tmp[(*i)] == '\\' && (tmp[(*i) + 1] == '"'
		|| tmp[(*i) + 1] == '\''))
	{
		str[(*j)++] = tmp[(*i)++];
		str[(*j)++] = tmp[(*i)++];
	}
	else if (tmp[(*i)] == '"')
	{
		(*i)++;
		while (tmp[(*i)] != '"')
			str[(*j)++] = tmp[(*i)++];
		(*i)++;
	}
	else if (tmp[(*i)] == '\'')
	{
		(*i)++;
		while (tmp[(*i)] != '\'')
			str[(*j)++] = tmp[(*i)++];
		(*i)++;
	}
	else
		str[(*j)++] = tmp[(*i)++];
}

void	ft_del_quotes(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = ft_strdup(str);
	i = 0;
	j = 0;
	while (i < ft_strlen(tmp))
		ft_del_quotes_aux(str, tmp, &j, &i);
	str[j] = 0;
	free(tmp);
	tmp = NULL;
}
