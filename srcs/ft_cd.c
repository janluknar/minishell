/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 11:11:58 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/09 10:56:38 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_not_found(t_shell *sh, int j)
{
	ft_printf("minishell: cd: %s: No such file or directory\n",
			sh->cmd[j].args[1]);
	sh->exit = 1;
}

char			*ft_chdirenv(int j, t_shell *sh)
{
	char	*temp;

	temp = ft_searchenv(sh->cmd[j].args[1] + 1, sh);
	if (!(ft_strcmp(temp, "")))
		return (ft_searchenv("HOME", sh));
	else
		return (temp);
}

void			ft_update_pwd(int j, t_shell *sh)
{
	t_command	micmd;
	t_command	micmd2;
	char		*temp1;
	char		*temp2;

	micmd.args = malloc(sizeof(char **) * 2);
	micmd2.args = malloc(sizeof(char **) * 2);
	temp1 = ft_strdup(sh->pwd);
	temp2 = 0;
	free(sh->pwd);
	sh->pwd = getcwd(temp2, 0);
	micmd.words = 2;
	micmd.args[0] = "export";
	micmd.args[1] = ft_strjoin("OLDPWD=", temp1);
	micmd2.words = 2;
	micmd2.args[0] = "export";
	micmd2.args[1] = ft_strjoin("PWD=", sh->pwd);
	ft_export(sh, &micmd);
	ft_export(sh, &micmd2);
	free(micmd.args);
	free(micmd.args[1]);
	free(micmd2.args);
	free(micmd2.args[1]);
	free(temp1);
}

static void		ft_cd_aux(t_shell *sh, char *temp, int j)
{
	ft_update_pwd(j, sh);
	free(sh->pwd);
	sh->pwd = getcwd(temp, 0);
	free(temp);
	temp = NULL;
	sh->exit = 0;
}

int				ft_cd(t_shell *sh, int j)
{
	int		ret;
	char	*temp;

	ret = 1;
	temp = NULL;
	if (sh->cmd[j].words == 1 || !(ft_strcmp(sh->cmd[j].args[1], "~")))
		ret = chdir(ft_searchenv("HOME", sh));
	else if (!(ft_strcmp(sh->cmd[j].args[1], "-")))
		ret = chdir(ft_searchenv("OLDPWD", sh));
	else if (!(ft_strcmp(sh->cmd[j].args[1], "..")))
		ret = chdir("..");
	else if (sh->cmd[j].args[1][0] == '$')
		ret = chdir(ft_chdirenv(j, sh));
	else if (!(ft_strcmp(sh->cmd[j].args[1], ".")))
		ret = chdir(sh->pwd);
	else
		ret = chdir(sh->cmd[j].args[1]);
	if (ret != -1)
		ft_cd_aux(sh, temp, j);
	else
		ft_not_found(sh, j);
	return (1);
}
