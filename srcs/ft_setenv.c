/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 13:21:34 by jluknar-          #+#    #+#             */
/*   Updated: 2020/09/08 13:21:50 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_set_environ(t_shell *sh)
{
	int			i;
	t_list_2	*cur;
	char		**environ;

	i = 0;
	cur = sh->list;
	while (cur)
	{
		cur = cur->next;
		i++;
	}
	environ = (char **)malloc(sizeof(char *) * (i + 1));
	cur = sh->list;
	i = 0;
	while (cur)
	{
		environ[i++] = cur->content;
		cur = cur->next;
	}
	environ[i] = NULL;
	(!sh->environ) ? NULL : free(sh->environ);
	sh->environ = environ;
}

int		ft_setenv(t_shell *sh, char *envp[])
{
	int			i;
	t_list_2	*aux;

	i = 0;
	while (envp[i])
		ft_lstadd_front_2(&sh->list, ft_lstnew_2(envp[i++]));
	ft_set_environ(sh);
	return (1);
}

int		ft_getenv(t_list_2 *lst)
{
	if (lst == NULL)
		return (2);
	while (lst)
	{
		write(1, lst->content, ft_strlen(lst->content));
		write(1, "\n", 1);
		lst = lst->next;
	}
	return (1);
}
