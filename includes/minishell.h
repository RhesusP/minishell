/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:28:41 by cbernot           #+#    #+#             */
/*   Updated: 2023/02/24 17:21:51 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./../libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

ls		cmd
-al		arg
------------
sortie cmd1 --> entree cmd2

cmd2 < cmd1
cmd1 > cmd2

|		pipe
------------
echo	cmd
bonjour	arg

typedef enum e_type {WORD, ARG, PIPE, REDIR, VAR}, t_type;

typedef struct	s_word
{
	char			*word;
	t_type			type;
	int				len;
	struct s_word	*next;
	struct s_word	*prev;
}	t_word;

typedef struct	s_command
{
	t_word	**words;	//chained list
	int		fd_out;
	int		fd_int;
}

typedef struct s_var_env
{
    char                *key;
    char                **values;
	struct s_var_env    *next;
}	t_var_env;

typedef struct s_global_env
{
    char					*key;
    char					**values;
	struct s_global_env		*next;
}	t_global_env;

void	signal_handler(void);
void	handle_ctrld(char *line);

# define SUCCESS	0
# define FAILURE	-1

#endif
