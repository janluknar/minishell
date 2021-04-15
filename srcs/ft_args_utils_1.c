/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 09:51:16 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/09 09:56:25 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_nq(char *arg, int *i, int *len)
{
	if (arg[*i] == '"')
	{
		(*len)++;
		(*i)++;
		while (arg[*i] != '"')
		{
			(*len)++;
			(*i)++;
		}
	}
	else if (arg[*i] == '\'')
	{
		(*len)++;
		(*i)++;
		while (arg[*i] != '\'')
		{
			(*len)++;
			(*i)++;
		}
	}
}

void	ft_fill_array(t_command *cmd)
{
	int	i;

	ft_free_array2d(cmd->args, cmd->words);
	cmd->words = cmd->cnt;
	cmd->args = (char **)malloc(sizeof(char *) * cmd->words + 1);
	i = 0;
	while (i < cmd->words)
	{
		cmd->args[i] = ft_strdup(cmd->aux[i]);
		i++;
	}
	cmd->args[i] = NULL;
}

void	ft_next_quote_args(char *line, char c, int *pi, int *plen)
{
	if (c == '"')
	{
		(*pi)++;
		while (line[*pi] != '"' && line[*pi] != '\0')
		{
			(*plen)++;
			(*pi)++;
		}
	}
	else if (c == '\'')
	{
		(*pi)++;
		while (line[*pi] != '\'' && line[*pi] != '\0')
		{
			(*plen)++;
			(*pi)++;
		}
	}
	(*pi)++;
}

void	ft_call_looks(t_shell *sh)
{
	ft_split_args(sh);
	ft_look_pipe(sh);
	ft_look_redir(sh);
	ft_look_redir_r(sh);
}
