/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:44:42 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/21 09:52:06 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

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
