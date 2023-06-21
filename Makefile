# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/01 00:23:19 by cbernot           #+#    #+#              #
#    Updated: 2023/06/21 19:11:47 by cbernot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = ./srcs/main.c ./srcs/signals.c ./srcs/structs/get_env.c ./srcs/structs/env_utils.c ./srcs/structs/env_utils2.c \
		./srcs/utils.c ./srcs/history.c \
		./srcs/tokenizer/parse_word.c ./srcs/structs/word_utils.c \
		./srcs/tokenizer/ft_strtok.c ./srcs/tokenizer/resplit.c \
		./srcs/tokenizer/set_type.c ./srcs/tokenizer/errors.c \
		./srcs/tokenizer/unquoted.c \
		./srcs/executer/executer.c ./srcs/executer/executer_utils.c ./srcs/executer/ft_execve.c \
		./srcs/structs/environment_utils.c ./srcs/structs/environment.c \
		./srcs/executer/get_next_cmd.c \
		./srcs/builtins/echo.c ./srcs/builtins/env.c \
		./srcs/builtins/export.c ./srcs/builtins/export_utils.c ./srcs/builtins/cd/cd.c ./srcs/builtins/cd/cd_utils.c  ./srcs/builtins/pwd.c \
		./srcs/builtins/exit.c ./srcs/builtins/unset.c ./srcs/builtins/cd/change_pwd.c ./srcs/builtins/cd/recreate_new_path.c \
		./srcs/free.c ./srcs/redirection/redir_utils.c\
		./srcs/structs/create_env.c \
		./srcs/structs/redirection.c ./srcs/redirection/redir_handler.c ./srcs/executer/tubes.c ./srcs/builtins/builtin_handler.c \
		./srcs/syntax.c ./srcs/structs/to_free.c ./srcs/builtins/cd/simplify_path.c \
		./srcs/structs/parse_param_utils.c \
		./srcs/expansion/var_expansion.c ./srcs/expansion/expansion_utils.c ./srcs/expansion/get_vars.c ./srcs/expansion/get_quoted_words.c \
		./srcs/expansion/get_key_name.c ./srcs/expansion/fill_quoted_tab.c ./srcs/expansion/get_values.c 

OBJS = ${SRCS:.c=.o}
INCLUDES = ./includes
FLAGS = -g3
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