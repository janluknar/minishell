/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_w.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 13:26:54 by jluknar-          #+#    #+#             */
/*   Updated: 2020/09/08 13:31:13 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_exec_pid_redir(t_shell *sh, char **args, char *command, int fd)
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
	{
		sh->exit = WEXITSTATUS(status);
	}
	return (ret);
}

static int	ft_exec_pid_redir_r(t_shell *sh, char **args, char *command, int fd)
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
	{
		sh->exit = WEXITSTATUS(status);
	}
	return (ret);
}

void		ft_redir_greater(t_shell *sh, t_command *cmd, int *cnt, int *i)
{
	int		fd;
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	free(cmd->args[*i]);
	cmd->args[*i] = NULL;
	if (!ft_strcmp(cmd->args[*i + 1], ">"))
	{
		fd = open(cmd->args[*i += 2], O_WRONLY | O_APPEND, mode);
		if (fd < 0)
			fd = open(cmd->args[*i], O_WRONLY | O_CREAT | O_TRUNC, mode);
		(*cnt)--;
	}
	else
		fd = open(cmd->args[++(*i)], O_WRONLY | O_CREAT | O_TRUNC, mode);
	(*cnt)--;
	if (*cnt)
		close(fd);
	else
	{
		ft_add_path_redir(sh, cmd, cmd->args);
		ft_exec_pid_redir(sh, cmd->args, cmd->args[0], fd);
		close(fd);
	}
}

void		ft_redir_lower(t_shell *sh, t_command *cmd, int *cnt, int *i)
{
	int		fd;
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	free(cmd->args[*i]);
	cmd->args[*i] = NULL;
	if (!ft_strcmp(cmd->args[*i + 1], "<"))
	{
		fd = open(cmd->args[--(*i)], O_WRONLY | O_APPEND, mode);
		(*i)++;
		(*cnt)--;
	}
	else
		fd = open(cmd->args[(*i) + 1], O_RDONLY, mode);
	(*cnt)--;
	if (*cnt)
		close(fd);
	else
	{
		ft_add_path_redir(sh, cmd, cmd->args);
		ft_exec_pid_redir_r(sh, cmd->args, cmd->args[0], fd);
		close(fd);
	}
}

void		ft_redir_w(t_shell *sh, t_command *cmd, int pos)
{
	int	i;
	int	is_open;
	int	cnt_w;
	int	cnt_r;

	i = 0;
	if (ft_check_redir(cmd))
		return ;
	cnt_w = cmd->cnt_redir_w;
	cnt_r = cmd->cnt_redir_r;
	while (cmd->args[i])
	{
		if (!ft_strcmp(cmd->args[i], ">"))
			ft_redir_greater(sh, cmd, &cnt_w, &i);
		else if (!ft_strcmp(cmd->args[i], "<"))
			ft_redir_lower(sh, cmd, &cnt_r, &i);
		i++;
	}
}
