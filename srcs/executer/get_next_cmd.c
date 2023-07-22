/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:44:42 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/21 17:00:54 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

/**
 * @brief Check if a words list is null.
 * 
 * @param is_init 
 * @param current 
 * @return int 
 */
static int	is_lst_null(int *is_init, t_word *current)
{
	if (*is_init && !current)
	{
		*is_init = 0;
		current = 0;
		return (0);
	}
	return (1);
}

/**
 * @brief Get the next command in the word chained list.
 * @details Works exactly like get_next_line() function, but with
 * chained list.
 * @param lst The chained list in which to search for the command.
 * @param new_lst The chained list in which to store the command.
 * @return t_word** new_lst containing the command or null if there
 * is no more command.
 */
t_word	**get_next_cmd(t_word **lst, t_word ***new_lst)
{
	static t_word	*current = 0;
	static int		is_init = 0;
	t_word			*copy;

	if (!is_lst_null(&is_init, current))
		return (0);
	else if (is_init && current->next)
		current = current->next;
	else if (!is_init && !current)
	{
		is_init = 1;
		current = *lst;
	}
	while (current && current->type != PIPE)
	{
		if (current->word && current->word[0] != '\0')
		{
			copy = create_word(current->word);
			copy->type = current->type;
			add_back_word(*new_lst, copy);
		}
		current = current->next;
	}
	return (*new_lst);
}
