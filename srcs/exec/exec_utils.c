/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:37:14 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/03/01 12:49:24 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/exec.h"

/*
**	Check if the command is a builtin
**	and execute it if it is indeed a builtin
*/
int	is_builtin(char *cmd)
{
	if (cmd == "exit")
		//return(exec_exit(), SUCCESS)
	if (cmd == "export")
		//return(exec_export(), SUCCESS)
	if (cmd == "pwd")
		//return(exec_pwd(), SUCCESS)
	if (cmd == "unset")
		//return(exec_unset(), SUCCESS)
	if (cmd == "echo")
		//return(exec_echo(), SUCCESS)
	if (cmd == "env")
		//return(exec_env(), SUCCESS)
	return (FAILURE);
}

/*
**	Get the number of args for the execution of one programm
*/
int	get_arg_len(t_word *parse)
{
	int	i;

	i = 0;
	if (parse->type == WORD)
	{
		i++;
		parse=parse->next;
		while (parse && parse->type == ARG)
		{
			i++;
			parse=parse->next;
		}
	}
	return (i);
}

/*
**	Free char **
*/
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
