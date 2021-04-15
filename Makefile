SPATH	=	./srcs/
HPATH	=	./includes/
SRCS	=	$(SPATH)main.c $(SPATH)main_aux.c $(SPATH)ft_gnl.c \
		$(SPATH)ft_getargs.c \
		$(SPATH)utils.c $(SPATH)utils_1.c $(SPATH)utils_2.c \
		$(SPATH)utils_3.c $(SPATH)utils_4.c $(SPATH)ft_args_utils_1.c \
		$(SPATH)ft_export_utils.c $(SPATH)ft_setpwd.c \
		$(SPATH)ft_parse_quotes.c $(SPATH)ft_exec_command_utils.c \
		$(SPATH)ft_exec_command.c $(SPATH)miscellaneous.c \
		$(SPATH)ft_args_utils.c $(SPATH)ft_lists.c $(SPATH)ft_exit.c \
		$(SPATH)ft_pwd.c $(SPATH)ft_setenv.c $(SPATH)ft_export.c \
		$(SPATH)ft_unset.c $(SPATH)ft_echo.c $(SPATH)ft_echo_aux.c \
		$(SPATH)ft_cd.c $(SPATH)ft_echo_dollar.c \
		$(SPATH)ft_add_path.c $(SPATH)ft_look_pipe.c \
		$(SPATH)ft_look_redir_w.c $(SPATH)ft_look_redir_r.c \
		$(SPATH)ft_get_sub_data.c $(SPATH)ft_fill_sub.c \
	   	$(SPATH)ft_pipe_paths.c $(SPATH)ft_exec_multi_pipe.c \
		$(SPATH)ft_redir_w.c $(SPATH)ft_redir_pipe.c $(SPATH)ft_redir_paths.c

CC	=	gcc
CFLAG	=	-Wall -Werror -Wextra
OBJS	=	$(SRCS:.c=.o)
LIB	= $(SPATH)libshell.a
NAME	=	minishell

$(SPATH)%.o:	%.c
	$(CC) $(CFLAG) -c $‹

ALL:		$(LIB)

$(LIB):		$(OBJS)
		make -C $(SPATH)ft_printf/
		mv $(SPATH)ft_printf/libftprintf.a $(SPATH)
		ar -rcs $(LIB) $(OBJS)
		$(CC) $(CFLAG) -L$(SPATH) -l shell -o $(NAME) $(SPATH)libftprintf.a

clean:
		rm -rf $(LIB) $(SPATH)libftprintf.a $(SPATH)libshell.a

fclean:
		rm -rf $(NAME) $(LIB) $(OBJS) $(SPATH)libftprintf.a $(SPATH)libshell.a

re:	fclean $(LIB)

.PHONY:		clean fclean re
