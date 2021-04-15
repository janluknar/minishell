/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <jluknar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 10:23:06 by jluknar-          #+#    #+#             */
/*   Updated: 2020/09/09 10:32:59 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_searchenv_aux(t_shell *sh, char *exit)
{
	exit = ft_itoa(sh->exit);
	free(exit);
	return (exit);
}

char		*ft_searchenv(char *env, t_shell *sh)
{
	int		i;
	char	*exit;

	i = 0;
	exit = NULL;
	while (sh->environ[i])
	{
		if (env[0] == '?')
			return (ft_searchenv_aux(sh, env));
		else
			exit = ft_strjoin(env, "=");
		if (ft_strstr(sh->environ[i], exit))
		{
			free(exit);
			return (sh->environ[i] + ft_strlen(exit));
			sh->environ[i] -= ft_strlen(exit);
		}
		else
			free(exit);
		i++;
	}
	return ("");
}

void		ft_echo_aux_1(t_shell *sh, t_echo_misc *grp)
{
	if (grp->temp[1] == '$')
	{
		ft_putchar('"');
		if (grp->temp[ft_strlen(grp->temp) - 1] == '"')
		{
			grp->temp[ft_strlen(grp->temp) - 1] = '\0';
			grp->flag_quote = 1;
		}
		ft_putstr(ft_searchenv(grp->temp + 2, sh));
		if (grp->flag_quote)
			ft_putchar('"');
	}
	else
	{
		ft_putchar('"');
		if (grp->temp[ft_strlen(grp->temp) - 1] == '"')
		{
			grp->temp[ft_strlen(grp->temp) - 1] = '\0';
			grp->flag_quote = 1;
		}
		ft_putstr(grp->temp);
		if (grp->flag_quote)
			ft_putchar('"');
	}
}

void		ft_echo_aux_2(t_shell *sh, t_echo_misc *grp)
{
	grp->temp++;
	ft_putstr(grp->temp);
	grp->temp--;
	if (grp->temp != NULL)
	{
		free(grp->temp);
		grp->temp = NULL;
	}
}
