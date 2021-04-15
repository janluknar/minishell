/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 08:15:07 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/09 08:44:07 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_clean_arg(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		ft_del_quotes(str[i]);
		ft_del_scape(str[i]);
		i++;
	}
}

static void	ft_add_path_pipe_aux(t_shell *sh, char **tmp, int *i)
{
	if (!ft_strncmp(sh->environ[*i], "PATH=", 5))
		*tmp = ft_strstr(sh->environ[*i], "=");
	(*i)++;
}

int			ft_add_path_pipe(t_shell *sh, t_command *cmd, char *str, int pos)
{
	int		i;
	char	*tmp;
	char	**paths;

	tmp = NULL;
	i = 0;
	if (str[0] == '/' || (str[0] == '.' && str[1] == '/'))
		return (ft_exec_cmd(sh, cmd, pos));
	while (sh->environ[i])
		ft_add_path_pipe_aux(sh, &tmp, &i);
	if (!tmp)
		return (ft_exec_cmd(sh, cmd, pos));
	paths = ft_split(++tmp, ':');
	i = ft_aux_path(paths, str);
	if (paths[i] != NULL)
	{
		if (cmd->sub_pipe[pos].cmd[0] != NULL)
			free(cmd->sub_pipe[pos].cmd[0]);
		cmd->sub_pipe[pos].cmd[0] = ft_strdup(paths[i]);
	}
	i = ft_exec_cmd(sh, cmd, pos);
	ft_free_paths(paths);
	return (i);
}
