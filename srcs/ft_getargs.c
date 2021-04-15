/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getargs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 13:15:04 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/09 09:57:27 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_parse_cmd(t_shell *sh)
{
	unsigned int	i;
	int				j;

	i = 0;
	if (!ft_strlen(sh->line))
	{
		free(sh->cmd);
		sh->cmd = NULL;
		return ;
	}
	ft_split_scolon(sh);
	j = 0;
	while (j <= sh->scolon_count)
	{
		sh->cmd[j].words = ft_count_words(sh->cmd[j].scolon);
		sh->cmd[j].flag_pipe = 0;
		sh->cmd[j].flag_redir_w = 0;
		sh->cmd[j].flag_redir_r = 0;
		sh->cmd[j].cnt = 0;
		sh->cmd[j].args = (char **)malloc(sizeof(char *) * sh->cmd[j].words);
		j++;
	}
	ft_call_looks(sh);
}

static void	ft_set_full_line(t_shell *sh)
{
	if (!sh->line)
		sh->line = sh->buffer;
	else if (sh->buffer)
	{
		free(sh->line);
		sh->line = ft_strdup(sh->buffer);
		free(sh->buffer);
		sh->buffer = NULL;
	}
}

static void	ft_get_args_2(t_shell *sh)
{
	ft_set_full_line(sh);
	sh->fr = 0;
	sh->cont = 0;
	ft_strrtrim(sh->line);
	sh->scolon_count = ft_count_scolon(sh);
	if (sh->scolon_count)
		sh->cmd = (t_command *)malloc(sizeof(t_command)
				* (sh->scolon_count + 1));
	else
		sh->cmd = (t_command *)malloc(sizeof(t_command));
	ft_parse_cmd(sh);
}

static void	ft_set_nl(t_shell *sh)
{
	char *tmp;

	tmp = ft_strjoin(sh->buffer, "\n");
	free(sh->buffer);
	sh->buffer = tmp;
}

void		ft_get_args(t_shell *sh)
{
	int flag;

	sh->flag_simple = 0;
	sh->flag_double = 0;
	sh->fr = 1;
	flag = ft_get_next_quote(sh);
	if (ft_strlen(sh->line) && flag)
	{
		sh->flag_double = 0;
		ft_settemp(&sh->buffer, sh->line, sh->fr);
		sh->fr++;
		while ((flag = ft_get_next_quote(sh)))
		{
			write(1, "> ", 2);
			free(sh->line);
			sh->line = NULL;
			ft_set_nl(sh);
			ft_gnl(0, &sh->line);
			sh->line[ft_strlen(sh->line) - 1] = 0;
			ft_settemp(&sh->buffer, sh->line, sh->fr);
			sh->flag_simple = 0;
			sh->flag_double = 0;
		}
	}
	ft_get_args_2(sh);
}
