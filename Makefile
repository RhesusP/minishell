# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/01 00:23:19 by cbernot           #+#    #+#              #
#    Updated: 2023/03/08 14:55:48 by cbernot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLORS
#DEF_COLOR = \033[0;39m
#GRAY = \033[0;90m
#RED = \033[0;91m
#GREEN = \033[0;92m
#YELLOW = \033[0;93m
#BLUE = \033[0;94m
#MAGENTA = \033[0;95m
#CYAN = \033[0;96m
#WHITE = \033[0;97m

#NAME	=	minishell

#INC            :=    minishell.h
#INC_DIR        :=    includes/

#HEADERS        := $(addprefix $(INC_DIR), $(INC))

#SRC_DIR        :=	srcs/
#SRC            :=	main.c

#LIBFT_A			:=	libft/libft.a
#LIBFT_DIR		:=	./libft

#COMPILED = 0
#TOTAL_COMPILATION = $(shell ((echo ${SRC}) | wc -w | sed -e 's/^[ \t]*//'))

#OBJ_DIR        :=    obj/
#OBJ            :=    $(SRC:%.c=$(OBJ_DIR)%.o)

# Compiler
#CC            :=    cc
#CC_FLAGS      :=    
#-Wextra -Werror -Wall

#all: $(NAME)

#$(NAME): $(OBJ)
#	@$(MAKE) -C $(LIBFT_DIR)
#	@$(CC) $(CC_FLAGS) -lreadline $(OBJ) $(LIBFT_A) -o $@
#	@echo "$(_GREEN)compilation done$(_END)"

#$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
#	@mkdir -p $(@D)
#	@$(eval COMPILED=$(shell echo $$((${COMPILED}+1))))
#	@echo "$(_YELLOW)Compiling in progress ${COMPILED}/${TOTAL_COMPILATION}"
#	@$(CC) $(CC_FLAGS) -lreadline -I $(INC_DIR) -c $< -o $@

#clean:
#	@$(MAKE) clean -C $(LIBFT_DIR)
#	@rm -rf $(OBJ_DIR)
#	@echo "$(_RED)Everything removed"

#fclean: clean
#	@$(MAKE) fclean -C $(LIBFT_DIR)
#	@rm -rf $(NAME)

#re : fclean all

#.PHONY: all clean fclean re

NAME = minishell
SRCS = ./srcs/main.c ./srcs/signals.c ./srcs/get_env.c ./srcs/env_utils.c \
		./srcs/utils.c ./srcs/history.c ./srcs/parse_word.c ./srcs/word_utils.c \
		./srcs/ft_strtok.c \
		./srcs/exec/exec_redo.c ./srcs/exec/environment_utils.c ./srcs/exec/environment.c
OBJS = ${SRCS:.c=.o}
INCLUDES = ./includes
FLAGS = 
DIR_FLAG = --no-print-directory

%.o: %.c ./includes/minishell.h 
	cc ${FLAGS} -I ${INCLUDES} -c $< -o $@

${NAME}: ${OBJS}
	make ${DIR_FLAG} -C ./libft
	cc ${OBJS} -L ./libft -lft -lreadline -o ${NAME}

all: ${NAME}

clean:
	make ${DIR_FLAG} clean -C ./libft
	rm -f ${OBJS}

fclean: clean
	make ${DIR_FLAG} fclean -C ./libft
	rm -f ${NAME}

testexport:
	gcc srcs/exec/builtin/export.c srcs/exec/builtin/unset.c srcs/exec/environment_utils.c libft/ft_split.c libft/ft_substr.c  libft/ft_strlen.c srcs/exec/exec_utils.c && ./a.out

test2:
	gcc srcs/exec/environment_utils.c libft/ft_split.c libft/ft_substr.c  libft/ft_strlen.c libft/ft_calloc.c libft/ft_memset.c && ./a.out

testunset:
	gcc srcs/exec/builtin/unset.c srcs/exec/exec_utils.c srcs/exec/environment_utils.c libft/ft_split.c libft/ft_substr.c  libft/ft_strlen.c && ./a.out
re: fclean all
