/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:28:41 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/23 00:02:45 by cbernot          ###   ########.fr       */
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
# include <errno.h>
# include <sys/stat.h>

# define SUCCESS	0
# define FAILURE	-1

/*
	POSSIBLE TYPES:
		INIT		-->	(0)		given at initialization
		CMD 		-->	(1)		command name (exec)
		ARG			--> (2)		command's argument
		PIPE		-->	(3)		pipe (|)
		RI			-->	(4)		redirecting input (<)
		RO			-->	(5)		redirecting output (>)
		ARO			-->	(6)		appending redirecting output (>>)
		HE			-->	(7)		here documents (<<)
		FILEPATH	-->	(8)		file path (used for redirections)
		DELIMITER	-->	(9)		come after a here document 
		IGN			-->	(10)	ignore token (e.g. variable assignation followed by a pipe)
*/
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
	char		*line;
	int			*pids;
	char		**he_files;
	int			status;
	int			nb_pipes;
	int			in_hd;
	int			already_e;
	t_redir		**redir;
	char		**str_env;
	char		**full_cmd;
}	t_to_free;

typedef struct s_parse_p
{
	char	*str;
	int		i;
	int		l_a;
	int		cell;
}	t_parse_p;

extern t_to_free	g_gbl;

/* ************************************************************************** */
/*                                   PARSING                                  */
/* ************************************************************************** */
t_word		**parse_words(char *line);
void		set_type(t_word **lst);
int			is_unquoted(char *line, int c_index);
int			is_unquoted_metachar(char *line, int c_index);
int			is_unquoted_double_chevron(char *line, int c_index);

/* ************************************************************************** */
/*                                  EXPANSION                                 */
/* ************************************************************************** */
void		var_expansion(t_word **lst, t_env_var **e);
int			get_nb_quoted_words(char *str);
char		**fill_quoted_tab(char *str, int size);
char		**get_key_name(char *str);
char		*values_to_str(char **tab);
char		*get_values(char *key, t_env_var **lst);
char		*get_last_unquoted(char *str);
char		*remove_quotes(char *str);
char		**resplit(char *s);
char		*get_vars(char *str, t_env_var **env);

/* ************************************************************************** */
/*                                 REDIRECTION                                */
/* ************************************************************************** */
char		**handle_redirection(t_redir **lst, char **full_cmd, char *he_file);
int			handle_simple_redir(t_redir *current);
char		*here_doc(char *delim);
int			input_redirection(t_redir *current);
int			output_redirection(t_redir *current);
void		do_exec_redir(t_to_free *to_free, char ***full_cmd, int i);
int			type_is_redir(t_word *word);
t_redir		**get_redir(t_word **lst);

/* ************************************************************************** */
/*                                  EXECUTION                                 */
/* ************************************************************************** */
void		ft_execve(t_to_free *f, t_env_var *path, int index, int nb_pipes);
void		execute_line(t_word	**word, t_env_var **env, char *line);
t_word		**get_next_cmd(t_word **lst, t_word ***new_lst);
char		*get_execve_path(char *cmd, t_env_var *path_var);
void		handle_execve_fail(t_to_free *f, char **cmd, char **env, int nb_p);
void		check_cmd_err(t_to_free *to_free, char **cmd, int nb_pipes);
void		unlink_he_files(t_to_free *to_free, int nb_pipes);
int			count_pipes(t_word **word);
char		*get_home(t_env_var *env);
char		**env_to_tab(t_env_var *env);
char		**lst_to_string(t_word **lst);

/* ************************************************************************** */
/*                                  BUILTINS                                  */
/* ************************************************************************** */
int			execute_builtin(t_word **lst, t_env_var **env, int nb_pipes);
int			execute_non_fork_builtin(int nb_pipes);
int			get_nb_arg(t_word **lst);
/* ------- ENV ------ */
void		ft_env(t_word **lst, t_env_var *env);
/* ------ PWD ------- */
void		ft_pwd(void);
char		*ft_getcwd(void);
/* ------- CD ------- */
void		ft_cd(t_word **lst, t_env_var *env);
char		*recreate_new_path(char **tab, int size);
void		simplify_path(char *str, t_env_var *env);
void		switch_old_curr_pwd(t_env_var *env);
void		change_pwd(t_env_var *env, char *new_pwd);
char		**create_dir_tab(char *str, int nb_dir);
int			count_dir(char *path);
/* ------ EXIT ------ */
void		ft_exit(t_to_free to_free);
/* ----- EXPORT ----- */
void		ft_export(t_word **lst, t_env_var **e, int forked, int n_pipe);
void		print_export(t_env_var *env);
t_env_var	*create_sorted_env_var(t_env_var *env);
int			is_already_here(t_env_var **env, char *key);
int			is_export_syntax_valid(char *str);
/* ----- UNSET ----- */
void		ft_unset(t_word **lst, t_env_var **env);
/* ------ ECHO ----- */
void		ft_echo(t_word **lst);

/* ************************************************************************** */
/*                                 STRUCT UTILS                               */
/* ************************************************************************** */
/* ----- T_ENV_VAR ----- */
t_env_var	*create_env_var(char *line);
void		add_back_env_var(t_env_var **lst, t_env_var *new);
char		*get_var_key(char *str);
char		**get_var_values(char *str);
t_env_var	*get_environment(char **env);
t_env_var	*get_env_custom(char *key_to_find, t_env_var *env);
t_env_var	*get_pwd(t_env_var *env);
t_env_var	*get_old_pwd(t_env_var *env);
/* ----- T_TO_FREE ----- */
void		init_to_free(int nb_pipes, t_word **word, char *line);
/* ------- T_WORD ------ */
t_word		*create_word(char *cmd);
void		add_back_word(t_word **lst, t_word *new);
void		delete_word(t_word *word, t_word **lst);
void		clear_word_lst(t_word **lst);
/* ------ T_REDIR ------ */
t_redir		*create_redir(t_type type, char *path);
void		add_back_redir(t_redir **lst, t_redir *new);

/* ************************************************************************** */
/*                                   SIGNALS                                  */
/* ************************************************************************** */
void		signal_handler(int sig);
void		get_sig_event(int status);
void		handle_ctrld(char *line, t_env_var *env);

/* ************************************************************************** */
/*                                    UTILS                                   */
/* ************************************************************************** */
char		*ft_strndup(const char *s1, unsigned int size);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strjoin_nullable(char *s1, char *s2);
int			ft_isspace(const char c);
int			is_metachar(char c);
char		**ft_strtok(char *str, char *charset);
char		*join_tab(char **tab, int size);
char		**copy_string_array(char **tab);
int			syntax_error(t_word **lst);

/* ************************************************************************** */
/*                                 FREE MEMORY                                */
/* ************************************************************************** */
void		free_all(char **str);
void		free_word_lst(t_word **lst);
void		ft_free(t_env_var *env);
void		free_redir(t_redir **redir);
void		free_and_exit(t_to_free *f, int is_exit, int exit_status, int u);
void		free_env(t_env_var *env);

#endif
