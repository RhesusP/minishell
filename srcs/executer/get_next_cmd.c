/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:44:42 by cbernot           #+#    #+#             */
/*   Updated: 2023/06/15 15:29:02 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

t_word	**get_next_cmd(t_word **lst, t_word ***new_lst)
{
	static t_word	*current = 0;
	static int		is_init = 0;
	t_word			*copy;

	if (is_init && !current)
	{
		is_init = 0;
		current = 0;
		return (0);
	}
	else if (is_init && current->next)
		current = current->next;
	else if (!is_init && !current)
	{
		is_init = 1;
		current = *lst;
	}
	while (current && current->type != PIPE)
	{
		copy = create_word(current->word);
		copy->type = current->type;
		add_back_word(*new_lst, copy);
		current = current->next;
	}
	return (*new_lst);
}
