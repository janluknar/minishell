/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 09:01:49 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/09 16:35:01 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_exec_pipe_redir_w(t_shell *sh, char **args, char *command, int fd)
{
	int		ret;
	int		i;
	int		status;
	pid_t	pid;

	if ((pid = fork()) == 0)
	{
		dup2(fd, 1);
		ret = execve(command, args, sh->environ);
		if (ret == -1)
		{
			ft_printf("-minishell: %s: Command not found\n", args[0]);
			exit(-1);
		}
	}
	i = waitpid(pid, &status, 0);
	sh->exit = -1;
	if (WIFEXITED(status))
		sh->exit = WEXITSTATUS(status);
	return (ret);
}

int		ft_exec_pipe_redir_r(t_shell *sh, char **args, char *command, int fd)
{
	int		ret;
	int		i;
	int		status;
	pid_t	pid;

	if ((pid = fork()) == 0)
	{
		dup2(fd, 0);
		ret = execve(command, args, sh->environ);
		if (ret == -1)
		{
			ft_printf("-minishell: %s: Command not found\n", args[0]);
			exit(-1);
		}
	}
	i = waitpid(pid, &status, 0);
	sh->exit = -1;
	if (WIFEXITED(status))
		sh->exit = WEXITSTATUS(status);
	return (ret);
}

void	ft_redir_gt_pipe(t_shell *sh, t_cmd_pipe *cmd, int *cnt, int *i)
{
	int		fd;
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	free(cmd->cmd[*i]);
	cmd->cmd[*i] = NULL;
	if (!ft_strcmp(cmd->cmd[*i + 1], ">"))
	{
		fd = open(cmd->cmd[*i += 2], O_WRONLY | O_APPEND, mode);
		if (fd < 0)
			fd = open(cmd->cmd[*i], O_WRONLY | O_CREAT | O_TRUNC, mode);
		(*cnt)--;
	}
	else
		fd = open(cmd->cmd[++(*i)], O_WRONLY | O_CREAT | O_TRUNC, mode);
	(*cnt)--;
	if (*cnt)
		close(fd);
	else
	{
		ft_add_path_redir_pipe(sh, cmd, cmd->cmd);
		ft_exec_pipe_redir_w(sh, cmd->cmd, cmd->cmd[0], fd);
		close(fd);
	}
}

void	ft_redir_lt_pipe(t_shell *sh, t_cmd_pipe *cmd, int *cnt, int *i)
{
	int		fd;
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	free(cmd->cmd[*i]);
	cmd->cmd[*i] = NULL;
	if (!ft_strcmp(cmd->cmd[*i + 1], "<"))
	{
		fd = open(cmd->cmd[--(*i)], O_WRONLY | O_APPEND, mode);
		(*i)++;
		(*cnt)--;
	}
	else
		fd = open(cmd->cmd[(*i) + 1], O_RDONLY, mode);
	(*cnt)--;
	if (*cnt)
		close(fd);
	else
	{
		ft_add_path_redir_pipe(sh, cmd, cmd->cmd);
		ft_exec_pipe_redir_r(sh, cmd->cmd, cmd->cmd[0], fd);
		close(fd);
	}
}

void	ft_redir_pipe_w(t_shell *sh, t_cmd_pipe *cmd, int pos)
{
	int	i;
	int	is_open;
	int	cnt_w;
	int	cnt_r;

	i = 0;
	cnt_w = cmd->cnt_redir_w;
	cnt_r = cmd->cnt_redir_r;
	while (cmd->cmd[i])
	{
		if (!ft_strcmp(cmd->cmd[i], ">"))
			ft_redir_gt_pipe(sh, cmd, &cnt_w, &i);
		else if (!ft_strcmp(cmd->cmd[i], "<"))
			ft_redir_lt_pipe(sh, cmd, &cnt_r, &i);
		i++;
	}
}
