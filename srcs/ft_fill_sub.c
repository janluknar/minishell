/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <jluknar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:53:08 by jluknar-          #+#    #+#             */
/*   Updated: 2020/09/08 16:31:06 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_count_redirs(t_command *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (i <= cmd->cnt_pipes)
	{
		j = 0;
		while (cmd->sub_pipe[i].cmd[j])
		{
			if (!ft_strcmp(cmd->sub_pipe[i].cmd[j], ">"))
				cmd->sub_pipe[i].cnt_redir_w++;
			if (!ft_strcmp(cmd->sub_pipe[i].cmd[j], "<"))
				cmd->sub_pipe[i].cnt_redir_r++;
			j++;
		}
		cmd->sub_pipe[i].flag_redir_w = cmd->sub_pipe[i].cnt_redir_w;
		cmd->sub_pipe[i].flag_redir_r = cmd->sub_pipe[i].cnt_redir_r;
		i++;
	}
}

void	ft_fill_sub(t_command *cmd)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	ft_get_sub_data(cmd);
	while (cmd->args[j])
	{
		if (!ft_strcmp(cmd->args[j], "|"))
		{
			i++;
			k = 0;
		}
		else
			cmd->sub_pipe[i].cmd[k++] = ft_strdup(cmd->args[j]);
		j++;
	}
	ft_count_redirs(cmd);
}
