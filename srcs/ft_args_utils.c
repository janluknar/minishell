/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 09:50:50 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/09 09:53:14 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_grp_counter_init(t_counters *grp)
{
	grp->i = 0;
	grp->j = 0;
	grp->k = 0;
	grp->start = 0;
	grp->len = 0;
}

static void	ft_split_args_aux(t_shell *sh, t_counters *grp)
{
	while (grp->i < ft_strlen(sh->cmd[grp->j].scolon))
	{
		if (sh->cmd[grp->j].scolon[grp->i] == '"'
				|| sh->cmd[grp->j].scolon[grp->i] == '\'')
		{
			ft_next_quote_args(sh->cmd[grp->j].scolon,
					sh->cmd[grp->j].scolon[grp->i], &grp->i, &grp->len);
			grp->len += 2;
		}
		if (sh->cmd[grp->j].scolon[grp->i] == ' ')
		{
			sh->cmd[grp->j].args[grp->k] = ft_strsub(sh->cmd[grp->j].scolon,
					grp->start, grp->len);
			grp->len = 0;
			grp->k++;
			grp->start = ft_del_space(sh->cmd[grp->j].scolon, &grp->i);
			grp->i--;
		}
		grp->len++;
		grp->i++;
	}
}

void		ft_split_args(t_shell *sh)
{
	t_counters	grp;

	ft_grp_counter_init(&grp);
	while (grp.j <= sh->scolon_count)
	{
		grp.i = 0;
		grp.k = 0;
		grp.len = 0;
		grp.start = ft_del_space(sh->cmd[grp.j].scolon, &grp.i);
		ft_split_args_aux(sh, &grp);
		grp.len = ft_strlen(sh->cmd[grp.j].scolon) - grp.start;
		sh->cmd[grp.j].args[grp.k] = ft_strsub(sh->cmd[grp.j].scolon,
				grp.start, grp.len);
		free(sh->cmd[grp.j].scolon);
		sh->cmd[grp.j].scolon = NULL;
		grp.j++;
	}
}

void		ft_split_scolon(t_shell *sh)
{
	t_counters	grp;

	ft_grp_counter_init(&grp);
	grp.start = ft_del_space(sh->line, &grp.i);
	while (grp.i < ft_strlen(sh->line))
	{
		if (sh->line[grp.i] == '"' || sh->line[grp.i] == '\'')
		{
			ft_next_quote_args(sh->line, sh->line[grp.i], &grp.i, &grp.len);
			grp.len += 2;
		}
		if (sh->line[grp.i] == ';')
		{
			grp.i++;
			sh->cmd[grp.j].scolon = ft_substr(sh->line, grp.start, grp.len);
			grp.start = ft_del_space(sh->line, &grp.i);
			grp.i--;
			grp.len = 0;
			grp.j++;
		}
		grp.len++;
		grp.i++;
	}
	grp.len = ft_strlen(sh->line) - grp.start;
	sh->cmd[grp.j].scolon = ft_substr(sh->line, grp.start, grp.len);
}

int			ft_count_words(char *str)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	ft_strrtrim(str);
	if (ft_strlen(str))
		ret++;
	while (i < ft_strlen(str))
	{
		if (str[i] == '"' || str[i] == '\'')
			ft_next_quote(str, str[i], &i);
		if (str[i] == ' ')
		{
			ret++;
			ft_del_space(str, &i);
			i--;
		}
		i++;
	}
	return (ret);
}
