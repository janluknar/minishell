/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:14:08 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/09 09:23:23 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list_2	*ft_lstnew_2(void *content)
{
	t_list_2	*list;

	if (!(list = (t_list_2 *)malloc(sizeof(*list))))
		return (NULL);
	else
		list->content = ft_strdup(content);
	list->next = NULL;
	return (list);
}

void		ft_lstadd_front_2(t_list_2 **alst, t_list_2 *new)
{
	if (*alst)
		new->next = *alst;
	*alst = new;
}

void		ft_lstadd_back_2(t_list_2 **alst, t_list_2 *new)
{
	t_list_2	*list;

	if (alst == NULL || new == NULL)
		return ;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	if (alst != NULL)
	{
		list = *alst;
		while (list->next)
			list = list->next;
		list->next = new;
		list = new;
	}
}

void		ft_lstiter_2(t_list_2 *lst, void (*f)(void *))
{
	if (lst == NULL)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
