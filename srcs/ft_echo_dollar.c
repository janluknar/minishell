/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 08:14:20 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/10 10:32:20 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_echo_splitter_aux(t_shell *sh, t_command *cmd,
		t_echo_misc *grp, int i)
{
	int		j;
	char	**tmp;
	char	*aux;

	ft_del_quotes(cmd->args[i]);
	tmp = ft_split(cmd->args[i], ' ');
	j = 0;
	while (tmp[j])
	{
		if (tmp[j][0] == '$')
		{
			aux = ft_searchenv(tmp[j] + 2, sh);
			++aux;
			write(1, aux, ft_strlen(aux));
			write(1, " ", 1);
		}
		else
			ft_printf("%s ", tmp[j]);
		free(tmp[j]);
		j++;
	}
	if (grp->p < cmd->words)
		grp->p++;
	free(tmp);
}

static void	ft_counting_dollar(t_command *cmd, int i, int *cnt)
{
	int	j;

	j = 0;
	while (cmd->args[i][j])
	{
		if (cmd->args[i][j] == '$')
			(*cnt)++;
		j++;
	}
}

static void	ft_proc_minus_n(t_shell *sh, t_command *cmd, t_echo_misc *grp)
{
	while (grp->p < cmd->words)
	{
		ft_echo_aux_4(sh, grp);
		grp->p++;
	}
}

static void	ft_aux_call(t_shell *sh, t_echo_misc *grp)
{
	ft_echo_aux_4(sh, grp);
	grp->p++;
}

void		ft_check_arg_dollar(t_shell *sh, t_command *cmd, t_echo_misc *grp)
{
	int i;
	int cnt;

	i = 1;
	if (!ft_strcmp(cmd->args[i], "-n") || cmd->args[i][0] == '\'')
	{
		ft_proc_minus_n(sh, cmd, grp);
		return ;
	}
	while (i < cmd->words)
	{
		cnt = 0;
		if (!ft_strcmp(cmd->args[i], "$?"))
		{
			ft_echo_aux_4(sh, grp);
			grp->p++;
			break ;
		}
		ft_counting_dollar(cmd, i, &cnt);
		if (cnt >= 1)
			ft_echo_splitter_aux(sh, cmd, grp, i);
		else
			ft_aux_call(sh, grp);
		i++;
	}
}
