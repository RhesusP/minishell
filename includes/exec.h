/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:51:50 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/03/01 11:16:29 by tbarde-c         ###   ########.fr       */
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

/*
**	Execution functions
*/
char		**get_full_cmd(t_word *parse);

/*
**	Environment functions
*/
t_env_var	*get_env_custom(char *key_to_find, t_env_var *env);


#endif