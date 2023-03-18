/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:46:54 by cbernot           #+#    #+#             */
/*   Updated: 2023/03/18 20:43:09 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

// TODO return error int when syntax error ? (e.g. missing HE delimiter)
void	give_meta_type(t_word **lst)
{
	t_word	*word;

	if (!*lst)
		return ;
	word = *lst;
	while (word)
	{
		if (word->type == INIT)
		{
			if (ft_strcmp(word->word, "|") == 0)
				word->type = PIPE;
			else if (ft_strcmp(word->word, "<") == 0)
			{
				word->type = RI;
				if (!word->next)
					ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
				else
					word->next->type = FILEPATH;
			}
			else if (ft_strcmp(word->word, ">") == 0)
			{
				word->type = RO;
				if (!word->next)
					ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
				else
					word->next->type = FILEPATH;	
			}
			else if (ft_strcmp(word->word, ">>") == 0)
			{
				word->type = ARO;
				if (!word->next)
					ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
				else
					word->next->type = FILEPATH;
			}
			else if (ft_strcmp(word->word, "<<") == 0)
			{
				word->type = HE;
				if (!word->next)
					ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
				else
					word->next->type = DELIMITER;
			}
		}
		word = word->next;
	}
}

void	give_cmd_type(t_word **lst)
{
	t_word	*word;

	if (!*lst)
		return ;
	word = *lst;
	while (word)
	{
		if (!word->prev)
		{
			if (ft_strchr(word->word, '='))
			{
				printf("%s is a variable assignation\n", word->word);
				//TODO add variable and free first word/token.
				*lst = word->next;
				printf("next is %s (%s)\n", word->next->word, print_type(word->next->type));
				if (word->next->type == INIT)
					word->next->type = CMD;
				else if (word->next->type == PIPE)	//TODO need to free here lol
					*lst = word->next->next;
			}
			else if (word->type == INIT)
				word->type = CMD;
		}
		else if(word->prev->type == PIPE)
			word->type = CMD;
		word = word->next;
	}
}

void	set_type(t_word **lst, t_env_var *envs, t_env_var *globals)
{
	t_word	*current;

	give_meta_type(lst);
	give_cmd_type(lst);
	if (!*lst)
		return ;
	current = *lst;
	while (current)
	{
		if (current->type == INIT)
			current->type = ARG;
		current = current->next;
	}
}