# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/01 00:23:19 by cbernot           #+#    #+#              #
#    Updated: 2023/05/26 10:43:08 by cbernot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = ./srcs/main.c ./srcs/signals.c ./srcs/structs/get_env.c ./srcs/structs/env_utils.c \
		./srcs/utils.c ./srcs/history.c \
		./srcs/tokenizer/parse_word.c ./srcs/structs/word_utils.c \
		./srcs/tokenizer/ft_strtok.c ./srcs/tokenizer/resplit.c \
		./srcs/tokenizer/set_type.c ./srcs/tokenizer/errors.c \
		./srcs/tokenizer/unquoted.c \
		./srcs/executer/executer.c ./srcs/executer/executer_utils.c \
		./srcs/structs/environment_utils.c ./srcs/structs/environment.c \
		./srcs/expansion/expansion_utils.c \
		./srcs/executer/get_next_cmd.c \
		./srcs/expansion/var_expansion.c \
		./srcs/builtins/echo.c ./srcs/builtins/env.c \
		./srcs/builtins/export.c ./srcs/builtins/cd.c ./srcs/builtins/pwd.c \
		./srcs/builtins/exit.c ./srcs/builtins/unset.c \
		./srcs/free.c ./srcs/redirection/redir_utils.c\
		./srcs/structs/create_env.c \
		./srcs/structs/redirection.c ./srcs/redirection/redir_handler.c ./srcs/executer/tubes.c ./srcs/builtins/builtin_handler.c \
		./srcs/syntax.c
OBJS = ${SRCS:.c=.o}
INCLUDES = ./includes
FLAGS = -g
#-g -fsanitize=address
#-Wall -Wextra -Werror
DIR_FLAG = --no-print-directory

%.o: %.c ./includes/minishell.h Makefile
	cc ${FLAGS} -I ${INCLUDES} -c $< -o $@

${NAME}: ${OBJS}
	make ${DIR_FLAG} -C ./libft
	cc ${OBJS} -L ./libft -lft -lreadline -o ${NAME}
#-g -fsanitize=address

all: ${NAME}

clean:
	make ${DIR_FLAG} clean -C ./libft
	rm -f ${OBJS}

fclean: clean
	make ${DIR_FLAG} fclean -C ./libft
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re