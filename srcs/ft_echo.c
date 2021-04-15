/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <jluknar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 11:30:29 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/10 08:58:41 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_echo_aux_3(t_shell *sh, t_echo_misc *grp)
{
	grp->temp = ft_strdup(sh->cmd[grp->j].args[grp->p]);
	ft_del_quotes(grp->temp);
	ft_putstr(grp->temp);
	if (grp->temp != NULL)
	{
		free(grp->temp);
		grp->temp = NULL;
	}
}

void		ft_echo_aux_generic(t_shell *sh, t_echo_misc *grp, int id)
{
	if (id == 0)
	{
		grp->temp = ft_strdup(sh->cmd[grp->j].args[grp->p]);
		ft_del_scape(grp->temp);
		if (grp->temp[0] == '"')
			ft_echo_aux_1(sh, grp);
		else
			ft_echo_aux_2(sh, grp);
	}
	else if (id == 1)
	{
		if (sh->cmd[grp->j].args[grp->p][0] == '"'
				&& sh->cmd[grp->j].args[grp->p][1] == '"')
			ft_del_quotes(sh->cmd[grp->j].args[grp->p]);
	}
	else if (id == 2)
	{
		ft_putstr(ft_searchenv(sh->cmd[grp->j].args[grp->p] + 1, sh));
		if (sh->cmd[grp->j].args[grp->p + 1])
			write(1, " ", 1);
	}
}

int			ft_check_echo_aux(t_shell *sh, t_echo_misc *grp, int j)
{
	grp->j = j;
	grp->flag = 0;
	grp->flag_quote = 0;
	grp->p = 1;
	grp->temp = NULL;
	if (sh->cmd[grp->j].words == 1)
		return (1);
	if (!(ft_strcmp(sh->cmd[grp->j].args[1], "-n")))
	{
		grp->flag = 1;
		grp->p = 2;
		return (1);
	}
	return (0);
}

void		ft_echo_aux_4(t_shell *sh, t_echo_misc *grp)
{
	ft_echo_aux_generic(sh, grp, 1);
	if (sh->cmd[grp->j].args[grp->p][0] == '\\')
		ft_echo_aux_generic(sh, grp, 0);
	else if (sh->cmd[grp->j].args[grp->p][0] == '"')
	{
		if (sh->cmd[grp->j].args[grp->p][1] == '$')
		{
			sh->cmd[grp->j].args[grp->p][ft_strlen(
					sh->cmd[grp->j].args[grp->p]) - 1] = '\0';
			ft_putstr(ft_searchenv(sh->cmd[grp->j].args[grp->p] + 2, sh));
			write(1, " ", 1);
		}
		else
			ft_echo_aux_3(sh, grp);
	}
	else if (sh->cmd[grp->j].args[grp->p][0] == '$')
		ft_echo_aux_generic(sh, grp, 2);
	else
		ft_putstr(sh->cmd[grp->j].args[grp->p]);
	if (sh->cmd[grp->j].args[grp->p + 1])
		ft_putchar(' ');
}

int			ft_echo(t_shell *sh, int j)
{
	t_echo_misc	grp;

	if (ft_check_echo_aux(sh, &grp, j))
		write(1, "", 1);
	while (grp.p < sh->cmd[grp.j].words)
		ft_check_arg_dollar(sh, &sh->cmd[j], &grp);
	(grp.flag == 0) ? write(1, "\n", 1) : 1;
	if (grp.temp != NULL)
	{
		free(grp.temp);
		grp.temp = NULL;
	}
	sh->exit = 0;
	return (1);
}
