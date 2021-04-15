/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_command_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 10:13:23 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/09 12:51:44 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_error_redir(int id)
{
	if (id == 1)
		ft_printf("-minishell: syntax error near unexpected token `<'\n");
	else if (id == 2)
		ft_printf("-minishell: syntax error near unexpected token `>'\n");
	else if (id == 3)
		ft_printf("-minishell: syntax error near unexpected token `|'\n");
	return (-1);
}

int		ft_check_redir(t_command *cmd)
{
	int	i;

	while (i < cmd->words)
	{
		if ((!ft_strcmp(cmd->args[0], ">") || !ft_strcmp(cmd->args[0], "<")))
			return (ft_error_redir(1));
		if (!ft_strcmp(cmd->args[i], "<") &&
			((!ft_strcmp(cmd->args[i + 1], "<")
			|| !ft_strcmp(cmd->args[i + 1], ">"))))
			return (ft_error_redir(1));
		if ((!ft_strcmp(cmd->args[i], ">") && !ft_strcmp(cmd->args[i + 1], ">"))
			&& (!ft_strcmp(cmd->args[i + 2], ">")
			|| !ft_strcmp(cmd->args[i + 2], "<")))
		{
			cmd->words++;
			return (ft_error_redir(1));
		}
		if (!ft_strcmp(cmd->args[cmd->words - 1], "<")
			|| !ft_strcmp(cmd->args[cmd->words - 1], ">"))
			return (ft_error_redir(2));
		i++;
	}
	return (0);
}

int		ft_check_pipe(t_command *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->words)
	{
		if (!ft_strcmp(cmd->args[0], "|") || (!ft_strcmp(cmd->args[i], "|")
				&& (!ft_strcmp(cmd->args[i + 1], "|"))))
			return (ft_error_redir(3));
		if (!ft_strcmp(cmd->args[cmd->words - 1], "|"))
			return (ft_error_redir(3));
		i++;
	}
	return (0);
}

int		ft_exec_env(t_shell *sh, t_command *cmd)
{
	int	ret;

	ret = 1;
	if (cmd->words > 1)
	{
		ft_printf("env: %s: No such file or directory\n", cmd->args[1]);
		sh->exit = 1;
	}
	else
		ft_getenv(sh->list);
	return (ret);
}
