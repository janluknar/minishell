/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_multi_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 16:44:38 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/09 10:39:08 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_close_fds(t_command *cmd, int pos, int *pid, int *status)
{
	int	ret;

	ret = -1;
	waitpid(*pid, status, 0);
	close(cmd->sub_pipe[pos].fd[PIPE_IN]);
	if (cmd->sub_pipe[pos].position == 0)
		close(cmd->sub_pipe[pos].fd[PIPE_OUT]);
	if (cmd->sub_pipe[pos].position != 1)
		close(cmd->sub_pipe[pos - 1].fd[PIPE_OUT]);
	if (WIFEXITED(*status))
		ret = WEXITSTATUS(*status);
	return (ret);
}

static void	ft_selecting_exec(t_shell *sh, t_command *cmd, int *ret, int pos)
{
	if (ft_built_exec(sh, cmd, cmd->sub_pipe[pos].cmd[0], pos) == 2)
	{
		if (cmd->sub_pipe[pos].flag_redir_w || cmd->sub_pipe[pos].flag_redir_r)
			ft_redir_pipe_w(sh, &cmd->sub_pipe[pos], pos);
		else if ((*ret = execve(cmd->sub_pipe[pos].cmd[0],
						cmd->sub_pipe[pos].cmd, sh->environ)) < 0)
			ft_printf("-minishell: %s Command not found\n",
					cmd->sub_pipe[pos].cmd[0]);
	}
}

int			ft_exec_cmd(t_shell *sh, t_command *cmd, int pos)
{
	pid_t	pid;
	int		ret;
	int		status;

	ret = -1;
	if (pipe(cmd->sub_pipe[pos].fd))
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		dup2(cmd->sub_pipe[pos].fd[PIPE_IN], 1);
		if (cmd->sub_pipe[pos].position == 2
				|| cmd->sub_pipe[pos].position == 0)
			dup2(cmd->sub_pipe[pos - 1].fd[PIPE_OUT], 0);
		if (cmd->sub_pipe[pos].position == 0)
			dup2(cmd->stdo, 1);
		ft_selecting_exec(sh, cmd, &ret, pos);
		exit(ret);
	}
	else
		ret = ft_close_fds(cmd, pos, &pid, &status);
	return (ret);
}
