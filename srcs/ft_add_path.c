/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 12:10:42 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/09 13:07:49 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_paths(char **p)
{
	int	i;

	i = 0;
	if (!p)
		return ;
	while (p[i])
		free(p[i++]);
	free(p);
}

int		ft_exec_pid(t_shell *sh, char **args, char *command)
{
	int		ret;
	int		i;
	int		status;
	pid_t	pid;

	if ((pid = fork()) == 0)
	{
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
	if (sh->exit == 255)
		sh->exit = 127;
	return (ret);
}

int		ft_aux_path(char **paths, char *str)
{
	char	*tmp;
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	tmp = NULL;
	while (paths[i] && ret <= 0)
	{
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = ft_strjoin(tmp, str);
		free(tmp);
		ret = open(paths[i], O_RDONLY);
		if (ret > 0)
			break ;
		i++;
	}
	close(ret);
	return (i);
}

int		ft_add_path(t_shell *sh, char *str)
{
	int		i;
	char	*tmp;
	char	**paths;

	tmp = NULL;
	i = 0;
	if (str[0] == '/' || (str[0] == '.' && str[1] == '/'))
		return (ft_exec_pid(sh, sh->tmp, str));
	while (sh->environ[i])
	{
		if (!ft_strncmp(sh->environ[i], "PATH=", 5))
			tmp = ft_strstr(sh->environ[i], "=");
		i++;
	}
	if (!tmp)
		return (ft_exec_pid(sh, sh->tmp, str));
	paths = ft_split(++tmp, ':');
	i = ft_aux_path(paths, str);
	i = ft_exec_pid(sh, sh->tmp, paths[i]);
	ft_free_paths(paths);
	return (i);
}

int		ft_seek_in_path(t_shell *sh, t_command *cmd)
{
	int		i;

	if (cmd->words > 0)
		sh->tmp = (char **)malloc(sizeof(char *) * (cmd->words + 1));
	else
		sh->tmp = (char **)malloc(sizeof(char *) * 2);
	i = 0;
	while (i < cmd->words)
	{
		if (i > 0)
			ft_del_quotes(cmd->args[i]);
		ft_del_scape(cmd->args[i]);
		sh->tmp[i] = cmd->args[i];
		i++;
	}
	sh->tmp[i] = NULL;
	ft_add_path(sh, cmd->args[0]);
	free(sh->tmp);
	return (1);
}
