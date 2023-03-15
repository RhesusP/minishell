/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:46:54 by cbernot           #+#    #+#             */
/*   Updated: 2023/03/15 15:17:34 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	give_meta_type(t_word *word)
{
	if (ft_strcmp(word->word, "|") == 0)
		word->type = PIPE;
	else if (ft_strcmp(word->word, "<") == 0)
		word->type = RI;
	else if (ft_strcmp(word->word, ">") == 0)
		word->type = RO;
	else if (ft_strcmp(word->word, ">>") == 0)
		word->type = ARO;
	else if (ft_strcmp(word->word, "<<") == 0)
		word->type = HE;
}

void	give_filepath_type(t_word *word)
{
	if (word->next && word->next->type == RI)
		word->type = FILEPATH;
	else if (word->prev && word->prev->type == RO)
		word->type = FILEPATH;
	else if (word->next && word->next->type == ARO)
		word->type = FILEPATH;
	else if(word->prev && word->prev->type == HE)
		word->type = DELIMITER;
	//TODO gestion du here document ?
}

void	detect_patterns(t_word *word)
{
	//TODO need to detect variable assignation
	give_meta_type(word);
	give_filepath_type(word);
	/*
	if (!word->prev || word->prev->type == PIPE)
		word->type = CMD;
	if (word->type == CMD && word->prev && (word->prev->type == CMD || word->prev->type == ARG))
		word->type = ARG;
	*/
}


void	set_type(t_word **lst, t_env_var *envs, t_env_var *globals)
{
	t_word	*current;

	if (!*lst)
		return ;
	current = *lst;
	while (current)
	{
		detect_patterns(current);
		current = current->next;
	}
	display_words(lst);
}