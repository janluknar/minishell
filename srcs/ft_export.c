/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <jluknar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 13:29:09 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/09 11:29:00 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_compare(t_list_2 *lst, char *str)
{
	t_list_2	*tmp;
	char		*s1;
	char		*s2;
	int			i;

	tmp = lst;
	ft_get_sub_equal(str, &i);
	s1 = ft_strsub(str, 0, i);
	while (tmp)
	{
		s2 = ft_strsub(tmp->content, 0, i);
		if (!(ft_strcmp(s1, s2)))
		{
			free(tmp->content);
			tmp->content = ft_strdup(str);
			ft_free_local_str(s1, s2);
			return (1);
		}
		free(s2);
		s2 = NULL;
		tmp = tmp->next;
	}
	ft_free_local_str(s1, s2);
	return (0);
}

static int	ft_validate(char *str, t_shell *sh)
{
	int	i;
	int	flag_equal;

	i = 0;
	flag_equal = 0;
	ft_rtrim(str, ' ');
	if (str[0] == '=' || ((str[0] == '"' || str[0] == '\'') && (str[1] == ' ')))
	{
		ft_del_quotes(str);
		sh->exit = 0;
		return (ft_error_export(str));
	}
	while (str[i])
	{
		if (str[i] == '=')
		{
			flag_equal = 1;
			if (str[i - 1] == ' ' || str[i + 1] == ' ')
				return (ft_error_export(str));
		}
		i++;
	}
	if (!flag_equal)
		return (-1);
	return (1);
}

char		*ft_add_quotes(t_list_2 *lst)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = (char *)malloc(ft_strlen(lst->content) + 3);
	while (i < ft_strlen(lst->content))
	{
		tmp[j] = lst->content[i];
		if (lst->content[i] == '=')
		{
			j++;
			tmp[j] = '"';
		}
		i++;
		j++;
	}
	tmp[j++] = '"';
	tmp[j] = 0;
	return (tmp);
}

int			ft_write_export(t_shell *sh)
{
	char		*aux;
	int			ret;
	t_list_2	*tmp;

	ret = 1;
	tmp = sh->list;
	while (tmp)
	{
		aux = ft_add_quotes(tmp);
		write(1, "declare -x ", 11);
		write(1, aux, ft_strlen(aux));
		write(1, "\n", 1);
		free(aux);
		aux = NULL;
		tmp = tmp->next;
	}
	return (ret);
}

int			ft_export(t_shell *sh, t_command *cmd)
{
	int	i;
	int	flag;

	i = 1;
	if (cmd->words == 1)
		return (ft_write_export(sh));
	while (i < cmd->words)
	{
		flag = 1;
		if (ft_validate(cmd->args[i], sh) == -1)
			flag = 0;
		else if (flag)
		{
			ft_del_quotes(cmd->args[i]);
			if (!(ft_compare(sh->list, cmd->args[i])))
			{
				ft_lstadd_front_2(&sh->list,
				ft_lstnew_2(cmd->args[i]));
			}
		}
		i++;
	}
	ft_set_environ(sh);
	return (1);
}
