/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:28:41 by cbernot           #+#    #+#             */
/*   Updated: 2023/03/19 19:18:17 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
#include "./../libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# define SUCCESS	0
# define FAILURE	-1

/*
	POSSIBLE TYPES:
		INIT		-->		given at initialization
		CMD 		-->		command name (exec)
		ARG			--> 	command's argument
		PIPE		-->		pipe (|)
		RI			-->		redirecting input (<)
		RO			-->		redirecting output (>)
		ARO			-->		appending redirecting output (>>)
		HE			-->		here documents (<<)
		FILEPATH	-->		file path (used for redirections)
		DELIMITER	-->		come after a here document 
		IGN			-->		ignore token (e.g. variable assignation followed by a pipe)
*/
typedef enum e_type {INIT, CMD, ARG, PIPE, RI, RO, ARO, HE, FILEPATH, DELIMITER, IGN} t_type;

typedef struct	s_word
{
	char			*word;
	t_type			type;
	int				len;		//TODO remove
	struct s_word	*next;
	struct s_word	*prev;
}	t_word;

typedef struct	s_command
{
	t_word	**words;	//chained list
	int		fd_out;
	int		fd_int;
}	t_command;

typedef struct s_env_var				//TODO rename to a more generic name
{
    char                *key;
    char                **values;
	struct s_env_var    *next;
}	t_env_var;

/* SIGNALS */
void		signal_handler(void);
void		handle_ctrld(char *line);

/* ENVIRONMENT */
t_env_var	*get_environment(char **env);
t_env_var	*create_env_var(char *line);
void		add_back_env_var(t_env_var **lst, t_env_var *new);
t_env_var	*get_last_env_var(t_env_var *lst);

/* WORDS */
t_word		*create_word(char *cmd);
t_word		*get_last_word(t_word *lst);
void		add_back_word(t_word **lst, t_word *new);
void		display_words(t_word **lst);
void		clear_word_lst(t_word **lst);
void		free_word_lst(t_word **lst);
void		delete_word(t_word *word, t_word **lst);
void		reverse_display_words(t_word **lst);	//DEBUG

/* UNQUOTED CHAR */
int			is_unquoted(char *line, int c_index);
int			is_unquoted_metachar(char *line, int c_index);
int			is_unquoted_double_chevron(char *line, int c_index);

/* PARSING */
void		parse_words(char *line, t_env_var *envs, t_env_var **globals);
void		set_type(t_word **lst, t_env_var *envs, t_env_var **globals);
char		**resplit(char *s);
int			is_metachar(char c);

/* UTILS */
int			ft_strcmp(char *s1, char *s2);
char		*ft_strndup(const char *s1, unsigned int size);
char		**ft_strtok(char *str, char *charset);

int	is_cmd_anonymous(char *cmd);

/**
 * Added in branch exec_redo
**/

void		execute_line(t_word	*word_lst, t_env_var *env);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strjoin_custom(char const *s1, char const *s2);
int			count_pipes(t_word *word);

/* DEBUG */
void		print_env(t_env_var *env_var_lst);
char		*print_type(t_type type);

# define SUCCESS	0
# define FAILURE	-1

#endif
