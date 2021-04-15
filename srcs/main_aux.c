/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <jluknar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 10:47:56 by jluknar-          #+#    #+#             */
/*   Updated: 2020/09/09 10:51:24 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_builtin(t_shell *sh)
{
	sh->cnt_builtin = 7;
	ft_strcpy(sh->builtin[0], "cd");
	ft_strcpy(sh->builtin[1], "echo");
	ft_strcpy(sh->builtin[2], "pwd");
	ft_strcpy(sh->builtin[3], "env");
	ft_strcpy(sh->builtin[4], "export");
	ft_strcpy(sh->builtin[5], "unset");
	ft_strcpy(sh->builtin[6], "exit");
}

void	init_defaults(t_shell *sh, char *envp[])
{
	sh->buffer = NULL;
	sh->pwd = NULL;
	sh->line = NULL;
	sh->environ = NULL;
	sh->cnt_quotes = 0;
	sh->flag_simple = 0;
	sh->flag_double = 0;
	sh->flag_equal = 0;
	sh->fr = 0;
	ft_setenv(sh, envp);
	init_builtin(sh);
}
