/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:51:50 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/02/28 14:44:38 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/*
**	Exec utils
*/
int		get_arg_len(t_word *parse);
void	free_all(char **str);

/*
**	Execution functions
*/
char	**get_full_cmd(t_word *parse);


#endif