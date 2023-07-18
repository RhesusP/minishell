/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:46:54 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/17 16:47:29 by cbernot          ###   ########.fr       */
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

static void	sub_give_cmd_type(t_word *word, t_word **lst, t_env_var **globals)
{
	if (!word->prev && !word->next)
	{
		if (actualize_global_var(globals, word->word) == FAILURE)
			add_back_env_var(globals, create_env_var(word->word));
		clear_word_lst(lst);
	}
	else if (word->prev && word->prev->type == CMD)
		word->type = ARG;
	else if (!word->prev && word->next && word->next->type == INIT)
	{
		word->next->type = CMD;
		delete_word(word, lst);
	}
	if (word->prev && word->prev->type == PIPE)
	{
		delete_word(word->prev, lst);
		if (word->next)
			delete_word(word, lst);
		else
			word->prev->next = 0;
	}
}

static void	give_cmd_type(t_word **lst, t_env_var **globals)
{
	t_word	*word;

	if (!lst || !*lst)
		return ;
	word = *lst;
	while (word)
	{
		if (word->type == INIT)
		{
			if (ft_strrchr(word->word, '=') && word->word[0] != '=')
			{
				sub_give_cmd_type(word, lst, globals);
				if (!word->prev && word->next && word->next->type == PIPE)
				{
					delete_word(word->next, lst);
					delete_word(word, lst);
				}
			}
			else if (!word->prev || word->prev->type == PIPE)
				word->type = CMD;
		}
		word = word->next;
	}
}

void	set_type(t_word **lst, t_env_var **globals)
{
	t_word	*current;

	give_meta_type(lst);
	give_cmd_type(lst, globals);
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
