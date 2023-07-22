/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:29:10 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/21 16:52:01 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

/**
 * @brief Create a word object with the INIT default type.
 * 
 * @param cmd The word to store.
 * @return t_word* 
 */
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

/**
 * @brief Get the last word object of the chained list.
 * 
 * @param lst 
 * @return t_word* 
 */
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

/**
 * @brief Add a word to the end of a chained list.
 * 
 * @param lst Chained list.
 * @param new Element to add.
 */
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

/**
 * @brief Clear and free the content of the word_lst object (but not the
 * chained list itself)
 * 
 * @param lst 
 */
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

/**
 * @brief Delete a word from a chained list.
 * @details Delete a word and re-arrange pointers in the
 * chained list.
 * @param word The word to delete.
 * @param lst The chained list containing the word. 
 */
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
