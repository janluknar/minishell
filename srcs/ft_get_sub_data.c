/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_sub_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 16:38:17 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/08 16:53:50 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_release_sub(t_command *cmd)
{
	int		i;
	int		j;

	if (!cmd->flag_pipe)
		return ;
	i = 0;
	while (i <= cmd->cnt_pipes)
	{
		ft_free_array2d(cmd->sub_pipe[i].cmd, cmd->sub_pipe[i].cnt + 1);
		i++;
	}
	if (cmd->sub_pipe != NULL)
		free(cmd->sub_pipe);
}

int		ft_set_sub_cmd(t_cmd_pipe *sub, int sz)
{
	int	i;

	if (!(sub->cmd = (char **)malloc(sizeof(char *) * (sz + 1))))
		return (-1);
	sub->cnt = sz;
	sub->flag_pipe = 0;
	sub->flag_redir_w = 0;
	sub->flag_redir_r = 0;
	sub->cnt_redir_w = 0;
	sub->cnt_redir_r = 0;
	i = 0;
	while (i <= sz)
		sub->cmd[i++] = NULL;
	return (1);
}

void	ft_set_position(t_cmd_pipe *sub, int pos, int total)
{
	sub->is_pipe = 1;
	if (pos == 0)
		sub->position = 1;
	else if (pos == total)
		sub->position = 0;
	else
		sub->position = 2;
}

void	ft_get_sub_data(t_command *cmd)
{
	t_counters	grp;

	grp.i = 0;
	grp.j = 0;
	grp.k = 0;
	cmd->sub_pipe = NULL;
	if (!(cmd->sub_pipe = (t_cmd_pipe *)malloc(sizeof(t_cmd_pipe)
		* (cmd->cnt_pipes + 1))))
		return ;
	while (cmd->args[grp.i])
	{
		if (!ft_strcmp(cmd->args[grp.i], "|"))
		{
			ft_set_sub_cmd(&cmd->sub_pipe[grp.j], grp.k);
			ft_set_position(&cmd->sub_pipe[grp.j], grp.j, cmd->cnt_pipes);
			grp.k = 0;
			grp.j++;
		}
		else
			grp.k++;
		grp.i++;
	}
	ft_set_sub_cmd(&cmd->sub_pipe[grp.j], grp.k);
	ft_set_position(&cmd->sub_pipe[grp.j], grp.j, cmd->cnt_pipes);
}
