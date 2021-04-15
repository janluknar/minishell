/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 12:31:32 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/09 11:24:12 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_free_cmd(t_shell *sh)
{
	int	i;
	int	j;

	j = 0;
	while (j <= sh->scolon_count)
	{
		i = 0;
		while (i < sh->cmd[j].words)
		{
			free(sh->cmd[j].args[i]);
			sh->cmd[j].args[i] = NULL;
			i++;
		}
		free(sh->cmd[j].args);
		sh->cmd[j].args = NULL;
		j++;
	}
	free(sh->cmd);
	sh->cmd = NULL;
}

int			ft_built_exec(t_shell *sh, t_command *cmd, char *command, int j)
{
	int	ret;

	ft_del_quotes(cmd->args[0]);
	ft_del_scape(cmd->args[0]);
	ret = 2;
	if (!(ft_strcmp(command, sh->builtin[0])))
		ret = ft_cd(sh, j);
	else if (!(ft_strcmp(command, sh->builtin[1])))
		ret = ft_echo(sh, j);
	else if (!(ft_strcmp(command, sh->builtin[2])))
		ret = ft_pwd();
	else if (!(ft_strcmp(command, sh->builtin[3])))
		ret = ft_exec_env(sh, cmd);
	else if (!(ft_strcmp(command, sh->builtin[4])))
		ret = ft_export(sh, cmd);
	else if (!(ft_strcmp(command, sh->builtin[5])))
		ret = ft_unset(sh, cmd);
	else if (!(ft_strcmp(command, sh->builtin[6])))
		ret = (ft_exit(sh, cmd));
	return (ret);
}

void		ft_exec_pipe(t_shell *sh, t_command *cmd)
{
	int pos;

	if (ft_check_pipe(cmd) < 0 || ft_check_redir(cmd) < 0)
		return ;
	ft_fill_sub(cmd);
	pos = 0;
	cmd->stdo = dup(1);
	while (pos <= cmd->cnt_pipes)
	{
		ft_clean_arg(cmd->sub_pipe[pos].cmd);
		ft_add_path_pipe(sh, cmd, cmd->sub_pipe[pos].cmd[0], pos);
		pos++;
	}
	ft_release_sub(cmd);
}

static int	ft_exec_command_aux(t_shell *sh, int j, int *ret)
{
	*ret = ft_built_exec(sh, &sh->cmd[j], sh->cmd[j].args[0], j);
	if (!(*ret))
		return (0);
	else if (*ret == 2)
		ft_seek_in_path(sh, &sh->cmd[j]);
	return (*ret);
}

int			ft_exec_command(t_shell *sh)
{
	int	i;
	int	j;
	int	ret;

	if (!sh->cmd)
		return (1);
	j = 0;
	ret = 1;
	while (j <= sh->scolon_count)
	{
		if ((sh->cmd[j].flag_redir_w || sh->cmd[j].flag_redir_r)
			&& !sh->cmd[j].flag_pipe)
			ft_redir_w(sh, &sh->cmd[j], j);
		else if (sh->cmd[j].flag_pipe)
			ft_exec_pipe(sh, &sh->cmd[j]);
		else
		{
			ret = ft_exec_command_aux(sh, j, &ret);
			if (ret == 0)
				return (0);
		}
		j++;
	}
	ft_free_cmd(sh);
	return (ret);
}
