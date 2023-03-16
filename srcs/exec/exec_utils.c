/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:37:14 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/03/08 14:04:05 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/exec.h"
/**
*	@brief Check if the command is a builtin
*	and execute it if it is indeed a builtin
**/
/*int	is_builtin(char **cmd)
{
	if (cmd[0] == "exit")
		//return(exec_exit(), SUCCESS)
	if (cmd[0] == "export")
		//return(exec_export(), SUCCESS)
	if (cmd[0] == "pwd")
		//return(exec_pwd(), SUCCESS)
	if (cmd[0] == "unset")
		//return(exec_unset(), SUCCESS)
	if (cmd[0] == "echo")
		//return(exec_echo(), SUCCESS)
	if (cmd[0] == "env")
		//return(exec_env(), SUCCESS)
	return (FAILURE);
}*/

/**
*	@brief Free char **
**/
void	free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

/**
 * @brief Counts the number of pipe that were parsed
 * @return Number of pipes counted
**/
int	count_pipes(t_word *word)
{
	int	pipe_nbr;

	pipe_nbr = 0;
	while (word)
	{
		if (word->type == PIPE)
			pipe_nbr++;
		word = word->next;
	}
	return (pipe_nbr);
}