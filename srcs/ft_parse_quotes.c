/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 08:13:34 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/09 08:14:29 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_set_flag(t_shell *sh, char c)
{
	sh->quote = c;
	sh->cnt_quotes++;
	if (sh->cnt_quotes % 2 && sh->flag_simple == 0 && sh->quote == '"')
		sh->flag_double = 1;
	else if (sh->flag_simple == 0 && sh->quote == '"')
	{
		sh->flag_double = 0;
		sh->cnt_quotes = 0;
	}
	else if (sh->cnt_quotes % 2 && sh->flag_double == 0 && sh->quote == '\'')
		sh->flag_simple = 1;
	else if (sh->flag_double == 0 && sh->quote == '\'')
	{
		sh->flag_simple = 0;
		sh->cnt_quotes = 0;
	}
}

int			ft_get_next_quote(t_shell *sh)
{
	char	*tmp;
	int		i;

	sh->cnt_quotes = 0;
	if (sh->fr == 1)
		tmp = sh->line;
	else
		tmp = sh->buffer;
	i = 0;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == '\\' && (tmp[i + 1] == '"' || tmp[i + 1] == '\''))
			i++;
		else if (tmp[i] == '"' && sh->flag_simple == 0)
			ft_set_flag(sh, '"');
		else if (tmp[i] == '\'' && sh->flag_double == 0)
			ft_set_flag(sh, '\'');
		i++;
	}
	if (sh->flag_double || sh->flag_simple)
		return (1);
	else
		return (0);
}

void		ft_settemp(char **buffer, char *line, int fr)
{
	char	*aux;

	aux = NULL;
	if (fr == 1)
		*buffer = ft_strdup(line);
	else if (fr > 1)
	{
		aux = ft_strjoin(*buffer, line);
		free(*buffer);
		*buffer = ft_strdup(aux);
		free(aux);
		aux = NULL;
	}
}
