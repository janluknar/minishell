/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_look_redir_w.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 18:55:41 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/09 12:27:52 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_separate_redir_aux(t_command *cmd, t_counters *grp, char *arg)
{
	grp->ret = 1;
	if (grp->len != 0)
	{
		cmd->aux[cmd->cnt++] = ft_strsub(arg, grp->start, grp->len);
		grp->start = grp->len;
		grp->len = 0;
	}
	if (arg[grp->i] == '>' && arg[grp->i + 1] != '\0')
	{
		cmd->aux[cmd->cnt++] = ft_strsub(arg, grp->i, 1);
		grp->start = grp->i + 1;
		grp->len--;
	}
	cmd->cnt_redir_w++;
}

int			ft_separate_redir(t_command *cmd, char *arg)
{
	char		*tmp;
	t_counters	grp;

	grp.start = 0;
	grp.len = 0;
	grp.i = 0;
	grp.ret = 0;
	while (grp.i < ft_strlen(arg))
	{
		if (arg[grp.i] == '"' || arg[grp.i] == '\'')
		{
			ft_next_quote_args(arg, arg[grp.i], &grp.i, &grp.len);
			grp.len += 2;
		}
		if (arg[grp.i] == '>')
			ft_separate_redir_aux(cmd, &grp, arg);
		grp.len++;
		grp.i++;
	}
	cmd->aux[cmd->cnt++] = ft_strsub(arg, grp.start, grp.len);
	return (grp.ret);
}

static void	ft_is_redir_aux(t_command *cmd, t_counters *grp, char *arg)
{
	if (arg[grp->i] == '>')
	{
		cmd->flag_redir_w++;
		if (ft_strlen(arg) > 1)
			grp->flag = ft_separate_redir(cmd, arg);
		else
			cmd->cnt_redir_w++;
	}
	else if (arg[grp->i + 1] != '\0' && arg[grp->i + 1] == '>')
	{
		grp->i++;
		cmd->flag_redir_w++;
		if (ft_strlen(arg) > 1)
			grp->flag = ft_separate_redir(cmd, arg);
		else
			cmd->cnt_redir_w++;
	}
	grp->i++;
}

int			ft_is_redir(t_command *cmd, char *arg)
{
	t_counters	grp;

	grp.i = 0;
	grp.len = 0;
	grp.flag = 0;
	ft_rtrim(arg, ' ');
	if (!arg || ft_strlen(arg) <= 0)
		return (0);
	while (grp.i < ft_strlen(arg) && !grp.flag && arg[grp.i] != '\0')
	{
		if (arg[grp.i] == '"' || arg[grp.i] == '\'')
			ft_nq(arg, &grp.i, &grp.len);
		ft_is_redir_aux(cmd, &grp, arg);
	}
	if (!grp.flag)
		cmd->aux[cmd->cnt++] = ft_strdup(arg);
	return (1);
}

void		ft_look_redir(t_shell *sh)
{
	int	j;
	int	i;
	int	k;

	j = 0;
	k = 0;
	i = 0;
	if (ft_strlen(sh->cmd[j].args[0]) == 0)
		return ;
	while (j <= sh->scolon_count)
	{
		i = 0;
		sh->cmd[j].aux = (char **)malloc(sizeof(char *) * 4096);
		sh->cmd[j].cnt = 0;
		sh->cmd[j].cnt_redir_w = 0;
		while (i < sh->cmd[j].words)
			ft_is_redir(&sh->cmd[j], sh->cmd[j].args[i++]);
		ft_fill_array(&sh->cmd[j]);
		ft_free_array2d(sh->cmd[j].aux, sh->cmd[j].cnt);
		j++;
	}
}
