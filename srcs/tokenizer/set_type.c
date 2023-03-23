/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:46:54 by cbernot           #+#    #+#             */
/*   Updated: 2023/03/19 19:18:47 by cbernot          ###   ########.fr       */
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

// TODO review deleting conditions and prevs.
void	give_cmd_type(t_word **lst, t_env_var **globals)
{
	t_word	*word;

	if (!*lst)
		return ;
	word = *lst;
	while (word)
	{
		if (word->type == INIT)
		{
			// VARIABLE ASSIGNATION CASE 
			if (ft_strrchr(word->word, '='))
			{
				//printf("\033[31mvariable assignation detected\033[39m\n");
				//word->word[0] != '=' added, because if we have no key, we must consider the =something as a command
				if (!word->prev && !word->next && word->word[0] != '=')
				{
					//printf("\033[32mwe can execute this assignation\033[39m\n");
					//delete_word(word, lst);
					if (actualize_global_var(globals, word->word) == FAILURE)
					{
						printf("ADDBACK\n");
						add_back_env_var(globals, create_env_var(word->word));
					}
					clear_word_lst(lst);
				}
				// case		echo TOTO=toto
				else if (word->prev && word->prev->type == CMD)
				{
					printf("here 1 (%s)\n", word->word);
					word->type = ARG;
				}
				// case		TOTO=toto ls
				else if (!word->prev && word->next && word->next->type == INIT)
				{
					printf("here 2 (%s)\n", word->word);
					word->next->type = CMD;
					delete_word(word, lst);
				}
				// case		... | TOTO=toto 
				if (word->prev && word->prev->type == PIPE)
				{
					printf("here 3 (%s)\n", word->word);
					delete_word(word->prev, lst);
					if (word->next)
					{
						printf("here 4 (%s)\n", word->word);
						delete_word(word, lst);
					}
					else
					{
						printf("here 5 (%s)\n", word->word);
						word->prev->next = 0;
					}
				}
				if (!word->prev && word->next && word->next->type == PIPE)
				{
					//same here
					printf("here 6 (%s)\n", word->word);
					delete_word(word->next, lst);
					delete_word(word, lst);
				}
			}
			// COMMAND CASE
			else if (!word->prev || word->prev->type == PIPE)
			{
				printf("here 7 (%s)\n", word->word);
				word->type = CMD;
			}
		}
		word = word->next;
	}
}

void	set_type(t_word **lst, t_env_var *envs, t_env_var **globals)
{
	t_word	*current;

	give_meta_type(lst);
	give_cmd_type(lst, globals);

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