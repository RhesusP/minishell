/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:46:54 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/21 16:11:45 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

/**
 * @brief Set the type of the redirections ('<', '>', '>>' and '<<').
 * 
 * @param word 
 */
static void	give_redir_type(t_word *word)
{
	if (ft_strcmp(word->word, "<") == 0)
	{
		word->type = RI;
		if (word->next)
			word->next->type = FILEPATH;
	}
	else if (ft_strcmp(word->word, ">") == 0)
	{
		word->type = RO;
		if (word->next)
			word->next->type = FILEPATH;
	}
	else if (ft_strcmp(word->word, ">>") == 0)
	{
		word->type = ARO;
		if (word->next)
			word->next->type = FILEPATH;
	}
	else if (ft_strcmp(word->word, "<<") == 0)
	{
		word->type = HE;
		if (word->next)
			word->next->type = DELIMITER;
	}
}

/**
 * @brief Set the type of the metacharaters ('<', '>', '>>', '<<' and '|').
 * 
 * @param lst 
 */
static void	give_meta_type(t_word **lst)
{
	t_word	*word;

	if (!lst || !*lst)
		return ;
	word = *lst;
	while (word)
	{
		if (word->type == INIT)
		{
			if (ft_strcmp(word->word, "|") == 0)
				word->type = PIPE;
			else
				give_redir_type(word);
		}
		word = word->next;
	}
}

/**
 * @brief Set the type of the commands.
 * @details A command is the first word of the list or the first word right 
 * after a pipe. 
 * @param lst 
 */
static void	give_cmd_type(t_word **lst)
{
	t_word	*word;

	if (!lst || !*lst)
		return ;
	word = *lst;
	while (word)
	{
		if (word->type == INIT)
		{
			if (!word->prev || word->prev->type == PIPE)
				word->type = CMD;
		}
		word = word->next;
	}
}

/**
 * @brief Scans the word list and set the type of each word.
 * @details Browses the tokenized word list and set the type of each word.
 * It starts with the metacharaters (because we know how they look), then
 * the commands (they are the first untyped token in the list or the first 
 * untyped token after a pipe) and finally the arguments (the rest).
 * @param lst 
 */
void	set_type(t_word **lst)
{
	t_word	*current;

	give_meta_type(lst);
	give_cmd_type(lst);
	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		if (current->type == INIT)
			current->type = ARG;
		current = current->next;
	}
}
