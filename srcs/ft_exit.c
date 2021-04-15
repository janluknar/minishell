/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 13:17:54 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/09 10:44:45 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_error_exit(t_shell *sh, t_command *cmd)
{
	ft_printf("-minishell: exit: %s: numeric argument required\n",
			cmd->args[1]);
	sh->exit = 255;
	return (0);
}

int			ft_too_many_arguments(t_shell *sh, t_command *cmd)
{
	write(1, "exit\n", 5);
	write(1, "minishell: exit: too many arguments\n", 36);
	sh->exit = 1;
	return (1);
}

int			ft_exit(t_shell *sh, t_command *cmd)
{
	t_list_2	*tmp;

	sh->exit = 0;
	if (cmd->words > 1)
	{
		ft_strrtrim(cmd->args[1]);
		if (cmd->words > 2 && ft_isnum(cmd->args[1]))
			return (ft_too_many_arguments(sh, cmd));
		else if (ft_isnum(cmd->args[1]) && cmd->words == 2)
			sh->exit = ft_atoi(cmd->args[1]);
		else
			return (ft_error_exit(sh, cmd));
	}
	ft_free_cmd(sh);
	while (sh->list)
	{
		tmp = sh->list->next;
		free(sh->list->content);
		free(sh->list);
		sh->list = tmp;
	}
	return (0);
}
