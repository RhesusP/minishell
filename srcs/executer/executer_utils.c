/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:34:17 by cbernot           #+#    #+#             */
/*   Updated: 2023/05/26 09:34:21 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
*	@brief Get the number of args for the execution of one programm
**/
int	get_exec_len(t_word **lst)
{
	int		len;
	t_word	*current;

	len = 0;
	current = *lst;
	while (current && (current->type == CMD || current->type == ARG))
	{
		len++;
		current = current->next;
	}
	return (len);
}

/**
 * @brief Counts the number of pipe that were parsed
 * @return Number of pipes counted
**/
int	count_pipes(t_word **word)
{
	int		pipe_nbr;
	t_word	*current;

	pipe_nbr = 0;
	if (!*word)
		return (0);
	current = *word;
	while (current)
	{
		if (current->type == PIPE)
			pipe_nbr++;
		current = current->next;
	}
	return (pipe_nbr);
}
