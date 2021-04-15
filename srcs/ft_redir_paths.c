/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 08:46:22 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/09 09:00:19 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_free_array(char **tmp)
{
	if (*tmp != NULL)
		free(*tmp);
	*tmp = NULL;
}

static void	ft_add_paths_aux(t_shell *sh, char **tmp, int *i)
{
	if (!ft_strncmp(sh->environ[*i], "PATH=", 5))
		*tmp = ft_strstr(sh->environ[*i], "=");
	(*i)++;
}

int			ft_add_path_redir_pipe(t_shell *sh, t_cmd_pipe *cmd, char **str)
{
	int		i;
	char	*tmp;
	char	**paths;
	char	**aux;

	tmp = NULL;
	i = 0;
	aux = str;
	if (*aux[0] == '/' || (*aux[0] == '.' && *aux[1] == '/'))
		return (1);
	while (sh->environ[i])
		ft_add_paths_aux(sh, &tmp, &i);
	if (!tmp)
		return (1);
	paths = ft_split(++tmp, ':');
	i = ft_aux_path(paths, aux[0]);
	if (paths[i] != NULL)
	{
		if (aux[0] != NULL)
			free(aux[0]);
		aux[0] = ft_strdup(paths[i]);
	}
	ft_free_paths(paths);
	ft_free_array(&tmp);
	return (1);
}

int			ft_add_path_redir(t_shell *sh, t_command *cmd, char **str)
{
	int		i;
	char	*tmp;
	char	**paths;
	char	**aux;

	tmp = NULL;
	i = 0;
	aux = str;
	if (*aux[0] == '/' || (*aux[0] == '.' && *aux[1] == '/'))
		return (1);
	while (sh->environ[i])
		ft_add_paths_aux(sh, &tmp, &i);
	if (!tmp)
		return (1);
	paths = ft_split(++tmp, ':');
	i = ft_aux_path(paths, aux[0]);
	if (paths[i] != NULL)
	{
		if (aux[0] != NULL)
			free(aux[0]);
		aux[0] = ft_strdup(paths[i]);
	}
	ft_free_paths(paths);
	return (1);
}
