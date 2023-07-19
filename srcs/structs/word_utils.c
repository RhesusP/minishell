/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmeen <svanmeen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:29:10 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/19 13:10:23 by svanmeen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

/// @brief Create a new word and set to INIT his type
/// @param cmd word data
/// @return Malloc'd *t_word
t_word	*create_word(char *cmd)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return (0);
	word->word = ft_strdup(cmd);
	word->type = INIT;
	word->next = 0;
	word->prev = 0;
	return (word);
}

/// @brief Get last t_word from lst
/// @param lst lst of t_word
/// @return last t_word
static t_word	*get_last_word(t_word *lst)
{
	t_word	*current;

	if (!lst)
		return (0);
	current = lst;
	while (current->next)
		current = current->next;
	return (current);
}

/// @brief Add [new] to the end of the list
/// @param lst list
/// @param new element to add
void	add_back_word(t_word **lst, t_word *new)
{
	t_word	*last;

	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	last = get_last_word(*lst);
	new->prev = last;
	last->next = new;
}

void	clear_word_lst(t_word **lst)
{
	t_word	*current;
	t_word	*next;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		free(current->word);
		free(current);
		current = next;
	}
	*lst = 0;
}

void	delete_word(t_word *word, t_word **lst)
{
	t_word	*prev;
	t_word	*next;

	prev = word->prev;
	next = word->next;
	if (!next)
		prev->next = 0;
	else if (!prev)
	{
		*lst = next;
		next->prev = 0;
	}
	else
	{
		prev->next = next;
		next->prev = prev;
	}
}
