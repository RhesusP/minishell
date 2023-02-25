/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:28:41 by cbernot           #+#    #+#             */
/*   Updated: 2023/02/25 17:14:53 by cbernot          ###   ########.fr       */
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

typedef enum e_type {WORD, ARG, PIPE, REDIR, VAR} t_type;

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
}	t_command;

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

void	get_environment(t_var_env *var_env, char **env);


# define SUCCESS	0
# define FAILURE	-1

#endif
