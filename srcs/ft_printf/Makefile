# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jluknar- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/11 17:38:22 by jluknar-          #+#    #+#              #
#    Updated: 2019/12/19 15:23:54 by jluknar-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB = ar rcs
RM = rm -f

CC = gcc

CCFLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

SRC = ft_printf.c ft_printf_case_caller.c ft_printf_char.c ft_printf_str.c \
	  ft_printf_type_identifier.c ft_printf_int.c ft_printf_percentage.c \
	  ft_printf_unsigned.c ft_printf_addr.c ft_printf_hex.c ft_printf_itoa_base.c \
	  ft_printf_check_flags.c ft_printf_dash.c ft_printf_widthonly.c \
	  ft_printf_auxiliary_int_functions.c

OBJ = $(SRC:.c=.o)

INCLUDE = ft_printf.h

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all: $(NAME)

$(NAME):
	make -C ./libft/
	cp libft/libft.a ./$(NAME)
	gcc -c $(FLAGS) $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	make fclean -C ./libft/

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean
