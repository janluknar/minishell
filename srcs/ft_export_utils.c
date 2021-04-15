/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <jluknar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 09:59:35 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/09 11:38:02 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_error_export(char *str)
{
	ft_printf("minishell: bad assignment\n", str);
	return (-1);
}

void	ft_free_local_str(char *s1, char *s2)
{
	free(s1);
	free(s2);
	s1 = NULL;
	s2 = NULL;
}

void	ft_get_sub_equal(char *str, int *i)
{
	*i = 0;
	while (str[*i] != '=')
		(*i)++;
}
