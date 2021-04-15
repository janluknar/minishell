/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 10:52:12 by jluknar-          #+#    #+#             */
/*   Updated: 2020/09/10 09:41:28 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../srcs/ft_printf/ft_printf.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	1024
# endif
# define PIPE_IN		1
# define PIPE_OUT		0

typedef struct		s_cmd_pipe
{
	char			**cmd;
	int				fd[2];
	int				is_pipe;
	int				position;
	int				flag_pipe;
	int				flag_redir_w;
	int				cnt_redir_w;
	int				flag_redir_r;
	int				cnt_redir_r;
	int				cnt;
}					t_cmd_pipe;

typedef struct		s_list_2
{
	char			*content;
	struct s_list_2	*next;
}					t_list_2;

typedef struct		s_command
{
	char			**args;
	char			*scolon;
	char			**aux;
	int				words;
	int				echo_flag;
	int				i;
	int				cnt;
	int				flag_pipe;
	int				cnt_pipes;
	int				flag_redir_w;
	int				cnt_redir_w;
	int				flag_redir_r;
	int				cnt_redir_r;
	int				stdo;
	t_cmd_pipe		*sub_pipe;
}					t_command;

typedef struct		s_file
{
	char			*strbuf;
	char			*endl;
	int				rsz;
	long			len;
	long			pos;
}					t_file;

typedef struct		s_shell
{
	char			builtin[7][10];
	char			**environ;
	char			**tmp;
	char			*word;
	char			*line;
	char			*buffer;
	char			*pwd;
	char			quote;
	int				fd[2];
	int				cnt_builtin;
	int				cnt_quotes;
	int				flag_simple;
	int				flag_double;
	int				flag_equal;
	int				scolon_count;
	int				status;
	int				exit;
	size_t			fr;
	int				cont;
	t_list_2		*list;
	t_command		*cmd;
}					t_shell;

typedef struct		s_counters
{
	int				i;
	int				j;
	int				k;
	int				start;
	int				len;
	int				ret;
	int				flag;
}					t_counters;

typedef struct		s_echo_misc
{
	int				p;
	int				j;
	int				flag;
	int				flag_quote;
	char			*temp;
}					t_echo_misc;

int					ft_gnl(int const fd, char **line);
void				ft_get_args(t_shell *sh);
int					ft_exec_command(t_shell *sh);
t_list_2			*ft_lstnew_2(void *content);
void				ft_lstadd_front_2(t_list_2 **lst, t_list_2 *new);
void				ft_lstadd_back_2(t_list_2 **lst, t_list_2 *new);
void				ft_lstiter_2(t_list_2 *lst, void (*f)(void *));
void				del(void *content);
void				init_builtin(t_shell *sh);
void				init_defaults(t_shell *sh, char *envp[]);
int					ft_built_exec(t_shell *sh,
					t_command *cmd, char *cmd_arg, int pos);
int					ft_echo(t_shell *sh, int j);
int					ft_cd(t_shell *sh, int j);
int					ft_pwd(void);
int					ft_export(t_shell *sh, t_command *cmd);
int					ft_unset(t_shell *sh, t_command *cmd);
void				ft_env(const char *fstr);
int					ft_exit(t_shell *sh, t_command *cmd);
int					ft_getenv(t_list_2 *lst);
int					ft_exec_env(t_shell *sh, t_command *cmd);
int					ft_setenv(t_shell *sh, char **envp);
void				ft_set_environ(t_shell *sh);
int					ft_setenv(t_shell *sh, char *envp[]);
char				*ft_searchenv(char *env, t_shell *sh);
void				ft_setpwd(t_shell *pwd);
int					ft_count_scolon(t_shell *sh);
void				ft_strrtrim(char *str);
void				ft_separator(t_shell *sh);
int					ft_del_space(char *str, int *pi);
void				ft_del_scape(char *str);
void				ft_del_quotes(char *str);
char				*ft_set_equal(char *str);
void				ft_next_quote(char *str, char c, int *pi);
void				ft_nq(char *str, int *i, int *len);
void				ft_next_quote_args(char *str, char c, int *pi, int *plen);
void				ft_free_cmd(t_shell *sh);
void				ft_free_paths(char **p);
int					ft_aux_path(char **paths, char *str);
void				ft_get_word(t_shell *sh, char c);
void				ft_split_buff(t_shell *sh);
void				ft_parse_letters(t_shell *sh, unsigned int *pi);
void				ft_proc_quotes(t_shell *sh, char c, unsigned int *pi);
void				ft_split_scolon(t_shell *sh);
void				ft_split_args(t_shell *sh);
int					ft_count_words(char *str);
void				ft_look_pipe(t_shell *sh);
void				ft_look_redir(t_shell *sh);
void				ft_get_sub_data(t_command *cmd);
void				ft_fill_sub(t_command *sub);
void				ft_release_sub(t_command *cmd);
void				ft_clean_arg(char **str);
void				ft_call_looks(t_shell *sh);
int					ft_error_export(char *str);
void				ft_free_local_str(char *s1, char *s2);
void				ft_get_sub_equal(char *str, int *i);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *str);
void				ft_echo_aux_3(t_shell *sh, t_echo_misc *grp);
void				ft_echo_aux_generic(t_shell *sh, t_echo_misc *grp, int id);
int					ft_check_echo_aux(t_shell *sh, t_echo_misc *grp, int j);
void				ft_echo_aux_4(t_shell *sh, t_echo_misc *grp);
int					ft_echo(t_shell *sh, int j);
char				*ft_searchenv_aux(t_shell *sh, char *exit);
char				*ft_searchenv(char *env, t_shell *sh);
void				ft_echo_aux_1(t_shell *sh, t_echo_misc *grp);
void				ft_echo_aux_2(t_shell *sh, t_echo_misc *grp);
void				ft_putstr(char *str);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strsub(const char *str, unsigned int start, size_t len);
char				*ft_substr(const char *str, unsigned int start, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strcpy(char *dest, const char *src);
void				*ft_memcpy(void *dest, const void *src, size_t len);
char				**ft_split(char const *s, char c);
void				ft_rtrim(char *str, char c);
char				*ft_strstr(char *hstk, const char *ndl);
int					ft_isnum(char *s);
int					ft_atoi(const char *s);
char				*ft_itoa(int n);
void				ft_free_array2d(char **str, int len);
void				ft_fill_array(t_command *cmd);
int					ft_get_next_quote(t_shell *sh);
void				ft_settemp(char **buffer, char *line, int fr);
int					ft_add_path(t_shell *sh, char *str);
int					ft_add_path_pipe(t_shell *sh, t_command *cmd,
					char *str, int pos);
int					ft_seek_in_path(t_shell *sh, t_command *cmd);
int					ft_pipe_in_path(t_shell *sh, t_command *cmd);
int					ft_exec_pid(t_shell *sh, char **args, char *str);
int					ft_exec_cmd(t_shell *sh, t_command *cmd, int pos);
int					ft_exec_pipe_redir_w(t_shell *sh, char **args,
					char *command, int fd);
int					ft_exec_pipe_redir_r(t_shell *sh, char **args,
					char *command, int fd);
void				ft_redir_w(t_shell *sh, t_command *cmd, int pos);
int					ft_add_path_redir(t_shell *sh, t_command *cmd, char **str);
int					ft_add_path_redir_pipe(t_shell *sh, t_cmd_pipe *cmd,
					char **str);
void				ft_look_redir_r(t_shell *sh);
int					ft_is_redir_r(t_command *cmd, char *arg);
int					ft_separate_redir_r(t_command *cmd, char *arg);
void				ft_redir_pipe_w(t_shell *sh, t_cmd_pipe *cmd, int pos);
void				ft_redir_lt_pipe(t_shell *sh, t_cmd_pipe *cmd,
					int *cnt, int *i);
void				ft_redir_gt_pipe(t_shell *sh, t_cmd_pipe *cmd,
					int *cnt, int *i);
int					ft_check_pipe(t_command *cmd);
int					ft_check_redir(t_command *cmd);
int					ft_error_redir(int id);
int					ft_check_redir(t_command *cmd);
int					ft_check_pipe(t_command *cmd);
void				ft_check_arg_dollar(t_shell *sh, t_command *cmd,
					t_echo_misc *grp);
#endif
