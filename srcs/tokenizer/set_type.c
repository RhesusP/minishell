/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:46:54 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/21 11:34:20 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

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
