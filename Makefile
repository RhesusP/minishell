# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svanmeen <svanmeen@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/01 00:23:19 by cbernot           #+#    #+#              #
#    Updated: 2023/07/23 09:05:58 by svanmeen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
SRCS	=	./srcs/main.c \
			./srcs/free.c \
			./srcs/syntax.c \
			./srcs/utils.c \
			./srcs/tokenizer/ft_strtok.c \
			./srcs/tokenizer/parse_word.c \
			./srcs/tokenizer/resplit.c \
			./srcs/tokenizer/set_type.c \
			./srcs/tokenizer/unquoted.c \
			./srcs/structs/create_env.c \
			./srcs/structs/env_utils.c \
			./srcs/structs/environment.c \
			./srcs/structs/get_env.c \
			./srcs/structs/redirection.c \
			./srcs/structs/to_free.c \
			./srcs/structs/word_utils.c \
			./srcs/signals/exec_signal.c \
			./srcs/signals/signals.c \
			./srcs/redirection/redir_handler.c \
			./srcs/redirection/redir_utils.c \
			./srcs/expansion/expansion_utils.c \
			./srcs/expansion/fill_quoted_tab.c \
			./srcs/expansion/get_key_name.c \
			./srcs/expansion/get_quoted_words.c \
			./srcs/expansion/get_values.c \
			./srcs/expansion/get_vars.c \
			./srcs/expansion/var_expansion.c \
			./srcs/executer/cmd_errors.c \
			./srcs/executer/executer_utils.c \
			./srcs/executer/executer.c \
			./srcs/executer/ft_execve.c \
			./srcs/executer/get_next_cmd.c \
			./srcs/builtins/cd/cd_utils.c \
			./srcs/builtins/cd/cd.c \
			./srcs/builtins/cd/change_pwd.c \
			./srcs/builtins/cd/recreate_new_path.c \
			./srcs/builtins/cd/simplify_path.c \
			./srcs/builtins/export/export_utils.c \
			./srcs/builtins/export/export.c \
			./srcs/builtins/export/sort.c \
			./srcs/builtins/builtin_handler.c \
			./srcs/builtins/echo.c \
			./srcs/builtins/env.c \
			./srcs/builtins/exit.c \
			./srcs/builtins/pwd.c \
			./srcs/builtins/unset.c

LIBFT_DIR	=	libft/
LIBFT_NAME	=	libft.a
LIBFT		=	$(addprefix $(LIBFT_DIR), $(LIBFT_NAME))

OBJS 		=	${SRCS:.c=.o}
INCLUDES	=	./includes
FLAGS		=	-Wall -Wextra -Werror
DIR_FLAG	=	--no-print-directory

%.o: %.c | libft ./includes/minishell.h
	cc ${FLAGS} -I ${INCLUDES} -c $< -o $@

${NAME}:  ${OBJS} ${LIBFT}
	cc ${OBJS} -L ./libft -lft -lreadline -o ${NAME}

all: ${NAME}

libft:
	@make -C ${LIBFT_DIR}

clean:
	make ${DIR_FLAG} clean -C ./libft
	rm -f ${OBJS}

fclean: clean
	make ${DIR_FLAG} fclean -C ./libft
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re libft
