/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:28:41 by cbernot           #+#    #+#             */
/*   Updated: 2023/05/12 17:22:57 by cbernot          ###   ########.fr       */
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
# include <fcntl.h>

# define SUCCESS	0
# define FAILURE	-1
//#define _POSIX_C_SOURCE

extern int	g_status;

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
	struct s_word	*next;
	struct s_word	*prev;
}	t_word;

typedef struct	s_command
{
	t_word	**words;	//chained list
	int		fd_out;
	int		fd_int;
}	t_command;

typedef struct	s_redir
{
	t_type			type;
	char			*filepath;
	struct s_redir	*next;
}	t_redir;

typedef struct s_env_var
{
    char                *key;
    char                **values;
	struct s_env_var    *next;
}	t_env_var;

void		signal_handler(void);
void		handle_ctrld(char *line, t_env_var *env, t_env_var *global);

t_env_var	*get_environment(char **env);
t_env_var	*create_env_var(char *line);
void		add_back_env_var(t_env_var **lst, t_env_var *new);
t_env_var	*get_last_env_var(t_env_var *lst);
void		free_env_var(t_env_var *env_var);

int		actualize_global_var(t_env_var **globals, char *word);
void	replace_global_variables(t_env_var **globals, t_word **words_lst);
int		count_unquoted_dollars(char *word);
int		max_size_global_var(t_env_var **globals);
void	update_flag_quotes(char c, int *flag_quotes);
int		check_var_end(char c);
char	*copy_var_key(char *word, int i);
int		allocate_key_memory(char *word, int i);
void	replace_in_copy(int *i, int *j, char *value, char *word_cpy);
int		check_var_size(t_env_var **globals, char *word, int i);

t_word		*create_word(char *cmd);
t_word		*get_last_word(t_word *lst);
void		add_back_word(t_word **lst, t_word *new);
void		display_words(t_word **lst);
void		clear_word_lst(t_word **lst);
void		delete_word(t_word *word, t_word **lst);

int			is_unquoted(char *line, int c_index);
int			is_unquoted_metachar(char *line, int c_index);
int			is_unquoted_double_chevron(char *line, int c_index);

t_word		**parse_words(char *line, t_env_var **globals);
void		set_type(t_word **lst, t_env_var **globals);
char		**resplit(char *s);
int			is_metachar(char c);
int			check_quotes_err(char *line);

int			ft_strcmp(char *s1, char *s2);
char		*ft_strndup(const char *s1, unsigned int size);
char		**ft_strtok(char *str, char *charset);
void		free_all(char **str);

int	is_cmd_anonymous(char *cmd);

void		execute_line(t_word	**word, t_env_var **env, t_env_var **global);
int			count_pipes(t_word **word);
int			get_exec_len(t_word **lst);

t_word	**get_next_cmd(t_word **lst, t_word*** new_lst);

void	ft_echo(t_word **lst);
void	ft_env(t_word **lst, t_env_var *env);
void	ft_export(t_word **lst, t_env_var **env);
void	ft_cd(t_word **lst, t_env_var *env);
void	ft_pwd();
void	ft_exit(t_word **lst);
void	ft_unset(t_word **lst, t_env_var **env, t_env_var **global);

char	*get_home(t_env_var *env);
t_env_var	*get_pwd(t_env_var *env);

char	*get_var_key(char *str);
char	**get_var_values(char *str);

t_word	**var_expansion(t_word **words_lst, t_env_var **global_vars, t_env_var **env_vars);

char	**handle_redirection(t_redir **lst, char **full_cmd);
char	**lst_to_string(t_word **lst);
t_redir	**get_redir(t_word **lst);

t_env_var	*get_env_custom(char *key_to_find, t_env_var *env);
void		env_var_add_back(t_env_var **env_var, t_env_var *new);
t_env_var	*env_var_new(char *env);

void	delete_existing_key(t_env_var **env, char *key);
int		is_already_here(t_env_var **env, char *key);

char	**env_to_tab(t_env_var *env);

char	*ft_getcwd();

void	ft_free(t_env_var *env, t_env_var *global);
void	free_word_lst(t_word **lst);

# define SUCCESS	0
# define FAILURE	-1

#endif