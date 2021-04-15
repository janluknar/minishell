/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 13:18:58 by jluknar-          #+#    #+#             */
/*   Updated: 2020/09/09 19:22:54 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_set_equal(char *str)
{
	char	*tmp;
	int		i;

	tmp = (char *)malloc(ft_strlen(str) + 2);
	i = 0;
	while (str[i] != '\0')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i++] = '=';
	tmp[i] = 0;
	return (tmp);
}

static void	ft_delete_var(t_list_2 **lst, char *str)
{
	char		*s1;
	char		*s2;
	t_list_2	*prev;
	t_list_2	*ptr;

	s2 = ft_set_equal(str);
	prev = NULL;
	while ((*lst))
	{
		s1 = ft_strsub((*lst)->content, 0, ft_strlen(s2));
		if (!(ft_strcmp(s1, s2)))
			ft_printf("");
		else
			ft_lstadd_front_2(&prev, ft_lstnew_2((*lst)->content));
		ptr = (*lst)->next;
		free((*lst)->content);
		free((*lst));
		(*lst) = ptr;
		free(s1);
		s1 = NULL;
	}
	free(s2);
	s2 = NULL;
	free(*lst);
	*lst = prev;
}

static int	ft_check_env(t_shell *sh, t_command *cmd)
{
	if (cmd->words == 1)
	{
		ft_printf("unset: not enough arguments\n");
		sh->exit = 1;
		return (1);
	}
	if (!ft_strcmp(cmd->args[1], "=") || !ft_strcmp(cmd->args[1], "!"))
	{
		ft_printf("unset: %s: invalid parameter name\n", cmd->args[1]);
		sh->exit = 1;
		return (1);
	}
	return (0);
}

int			ft_unset(t_shell *sh, t_command *cmd)
{
	int	ret;
	int	i;

	ret = 1;
	i = 0;
	if (ft_check_env(sh, cmd) == 1)
		return (ret);
	while (i < cmd->words)
	{
		ft_rtrim(cmd->args[i], ' ');
		ft_del_quotes(cmd->args[i++]);
	}
	i = 1;
	while (i < cmd->words && cmd->words > 1)
	{
		ft_delete_var(&sh->list, cmd->args[i]);
		i++;
	}
	ft_set_environ(sh);
	return (ret);
}
