/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:51:50 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/03/08 11:22:45 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <fcntl.h>

/*
**	Exec utils
*/
int			get_arg_len(t_word *parse);
void		free_all(char **str);
int			is_builtin(char **cmd);

/*
**	Execution functions
*/
char		**get_full_cmd(t_word *parse);

/*
**	Builtins functions
*/
void		exec_echo(char **cmd);
void		exec_exit(char **cmd);
void		exec_env(t_env_var *var_env);

/*
**	Metacharacter functions
*/
int     	single_right_arrow(char *file_path, char *to_write);
int     	double_right_arrow(char *file_path, char *to_write);

/*
**	Environment functions
*/
t_env_var	*get_env_custom(char *key_to_find, t_env_var *env);
void		env_var_clear(t_env_var *env_var);
void		env_var_add_back(t_env_var **env_var, t_env_var *new);
t_env_var	*env_var_last(t_env_var *env_var);
t_env_var	*env_var_new(char *env);
t_env_var	*get_initial_env(char **env);





#endif