/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:28:41 by cbernot           #+#    #+#             */
/*   Updated: 2023/06/16 11:52:43 by cbernot          ###   ########.fr       */
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
# include <fcntl.h>

# define SUCCESS	0
# define FAILURE	-1

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
//                    0     1	 2    3    4   5    6   7       8         9
typedef enum e_type
{
	INIT,
	CMD,
	ARG,
	PIPE,
	RI,
	RO,
	ARO,
	HE,
	FILEPATH,
	DELIMITER,
	IGN
}	t_type;

typedef struct s_word
{
	char			*word;
	t_type			type;
	struct s_word	*next;
	struct s_word	*prev;
}	t_word;

typedef struct s_command
{
	t_word	**words;
	int		fd_out;
	int		fd_int;
}	t_command;

typedef struct s_redir
{
	t_type			type;
	char			*filepath;
	struct s_redir	*next;
}	t_redir;

typedef struct s_env_var
{
	char				*key;
	char				**values;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_to_free
{	
	t_word		**lst;
	t_word		**command;
	t_env_var	**env;
	t_env_var	**global;
	char		*line;
	int			**tubes;
}	t_to_free;

typedef struct s_parse_param
{
	char	*str;
	int		*i;
	int		*last_alloc;
	int		*cell;
}	t_parse_param;

char			*ft_strndup(const char *s1, unsigned int size);
int				ft_strcmp(char *s1, char *s2);
void			free_all(char **str);
char			*ft_strjoin_nullable(char *s1, char *s2);
int				ft_isspace(const char c);
int				syntax_error(t_word **lst);
void			signal_handler(void);
void			handle_ctrld(char *line, t_env_var *env, t_env_var *global);
void			free_word_lst(t_word **lst);
void			ft_free(t_env_var *env, t_env_var *global);
int				is_unquoted_double_chevron(char *line, int c_index);
int				is_unquoted_metachar(char *line, int c_index);
int				is_unquoted(char *line, int c_index);
void			set_type(t_word **lst, t_env_var **globals);
char			**resplit(char *s);
t_word			**parse_words(char *line, t_env_var **globals);
int				is_metachar(char c);
char			**ft_strtok(char *str, char *charset);
void			delete_word(t_word *word, t_word **lst);
void			clear_word_lst(t_word **lst);
void			add_back_word(t_word **lst, t_word *new);
t_word			*create_word(char *cmd);
void			free_and_exit(t_to_free f, int is_exit, int exit_status);
int				type_is_redir(t_word *word);
void			free_redir(t_redir **redir);
void			add_back_redir(t_redir **lst, t_redir *new);
t_redir			*create_redir(t_type type, char *path);
t_parse_param	init_parse_p(char *str, int *i, int *last_alloc, int *cell);
t_env_var		*get_environment(char **env);
t_env_var		*get_env_custom(char *key_to_find, t_env_var *env);
char			*get_home(t_env_var *env);
char			**env_to_tab(t_env_var *env);
int				is_already_here(t_env_var **env, char *key);
int				actualize_global_var(t_env_var **globals, char *word);
void			add_back_env_var(t_env_var **lst, t_env_var *new);
t_env_var		*create_env_var(char *line);
char			**get_var_values(char *str);
char			*get_var_key(char *str);
char			*here_doc(char *delim);
t_redir			**get_redir(t_word **lst);
char			**handle_redirection(t_redir **lst, char **full_cmd);
void			var_expansion(t_word **lst, t_env_var **g, t_env_var **e);
char			*get_vars(char *str, t_env_var **env, t_env_var **global);
char			*get_values(char *key, t_env_var **lst, t_env_var **global);
int				get_nb_quoted_words(char *str);
char			**get_key_name(char *str);
char			**fill_quoted_tab(char *str, int size);
char			*values_to_str(char **tab);
char			*remove_quotes(char *str);
char			*get_last_unquoted(char *str);
char			*join_tab(char **tab, int size);
void			free_tubes(int **tubes);
int				**create_tubes(int nb_tubes);
t_word			**get_next_cmd(t_word **lst, t_word ***new_lst);
void			ft_execve(t_to_free to_free, int count, int nb_pipes);
void			exec_ln(t_word	**word, t_env_var **e, t_env_var **g, char *ln);
char			*get_execve_path(char *cmd, t_env_var *path_var);
char			**lst_to_string(t_word **lst);
char			**copy_string_array(char **tab);
int				count_pipes(t_word **word);
void			ft_unset(t_word **lst, t_env_var **env, t_env_var **global);
char			*ft_getcwd(void);
void			ft_pwd(void);
void			ft_export(t_word **lst, t_env_var **e, int forked, int n_pipe);
int				get_nb_arg(t_word **lst);
int				is_export_syntax_valid(char *str);
void			print_export(t_env_var *env);
void			ft_exit(t_to_free to_free);
void			ft_env(t_word **lst, t_env_var *env);
void			ft_echo(t_word **lst);
int				execute_non_fork_builtin(t_to_free to_free, int nb_pipes);
int				execute_builtin(t_word **lst, t_env_var **env, int nb_pipes);
void			simplify_path(char *str, t_env_var *env);
char			*recreate_new_path(char **tab, int size);
void			change_pwd(t_env_var *env, char *new_pwd, int to_free);
void			ft_cd(t_word **lst, t_env_var *env);
void			switch_old_curr_pwd(t_env_var *env);
char			**create_dir_tab(char *str, int nb_dir);
int				count_dir(char *path);
t_env_var		*get_pwd(t_env_var *env);
t_env_var		*get_old_pwd(t_env_var *env);

#endif