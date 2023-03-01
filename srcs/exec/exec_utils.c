/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:37:14 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/02/28 15:44:14 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/exec.h"

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
