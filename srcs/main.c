/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <jluknar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 13:12:25 by jluknar-          #+#    #+#             */
/*   Updated: 2020/09/10 09:46:20 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sig_abort(int num)
{
	char str[1024];

	getcwd(str, 1024);
	write(1, "\b\b\n", 3);
	ft_putstr(str);
	write(1, "$ ", 2);
	signal(SIGINT, ft_sig_abort);
	return ;
}

void	ft_sig_stop(int num)
{
	char str[1024];

	kill(0, SIGSTOP);
	getcwd(str, 1024);
	ft_putstr(str);
	write(1, "$ ", 2);
	signal(SIGSTOP, ft_sig_stop);
}

void	ft_sig_quit(int num)
{
	kill(SIGCHLD, SIGQUIT);
	signal(SIGQUIT, ft_sig_quit);
}

void	init_shell(t_shell *sh)
{
	sh->status = 1;
	while (sh->status)
	{
		write(1, sh->pwd, ft_strlen(sh->pwd));
		write(1, "$ ", 2);
		ft_gnl(0, &sh->line);
		if (!sh->line || ft_strlen(sh->line) == 0)
		{
			write(1, "exit\n", 5);
			free(sh->line);
			sh->line = ft_strdup("exit");
		}
		else
			sh->line[ft_strlen(sh->line) - 1] = 0;
		ft_get_args(sh);
		sh->status = ft_exec_command(sh);
		free(sh->line);
		sh->line = NULL;
	}
}

int		main(int argc, char *argv[], char *envp[])
{
	t_shell	sh;

	sh.exit = 0;
	if (signal(SIGINT, ft_sig_abort) == SIG_ERR)
		ft_printf("Error registering SIGINT\n");
	if (signal(SIGTSTP, ft_sig_stop) == SIG_ERR)
		ft_printf("Error registering SIGTSTP\n");
	if (signal(SIGQUIT, ft_sig_quit))
		ft_printf("Error registering SIGQUIT\n");
	init_defaults(&sh, envp);
	ft_setpwd(&sh);
	init_shell(&sh);
	free(sh.pwd);
	return (sh.exit);
	(void)argc;
	(void)argv;
}
