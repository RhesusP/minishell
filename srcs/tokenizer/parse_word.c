/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 01:46:22 by cbernot           #+#    #+#             */
/*   Updated: 2023/06/15 09:30:57 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	is_metachar(char c)
{
	if (c == '|' || c == '(' || c == ')' || c == '<' || c == '>')
		return (1);
	return (0);
}

void	reparse_and_addback(t_word **new_lst, t_word *current)
{
	int		i;
	char	**reparse;

	i = 0;
	reparse = resplit(current->word);
	while (reparse[i])
	{
		add_back_word(new_lst, create_word(reparse[i]));
		i++;
	}
	i = 0;
	while (reparse[i])
	{
		free(reparse[i]);
		i++;
	}
	free(reparse);
}

t_word	**detect_close_pipe(t_word **lst)
{
	t_word	*c;
	t_word	**new_lst;

	if (!lst)
		return (0);
	new_lst = malloc(sizeof(t_word *));
	if (!new_lst)
		return (0);
	*new_lst = 0;
	c = *lst;
	while (c)
	{
		if (ft_strcmp(c->word, "<<") == 0 || ft_strcmp(c->word, ">>") == 0)
		{
			add_back_word(new_lst, create_word(c->word));
			c = c->next;
		}
		else
		{
			reparse_and_addback(new_lst, c);
			c = c->next;
		}
	}
	free_word_lst(lst);
	return (new_lst);
}

void	free_tokens(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

t_word	**parse_words(char *line, t_env_var **globals)
{
	char	**tokens;
	t_word	**words_lst;
	t_word	*word;
	int		i;

	words_lst = malloc(sizeof(t_word *));
	if (!words_lst)
		return (0);
	*words_lst = 0;
	tokens = ft_strtok(line, " \n\t");
	i = 0;
	while (tokens[i])
	{
		word = create_word(tokens[i]);
		add_back_word(words_lst, word);
		i++;
	}
	free_tokens(tokens);
	words_lst = detect_close_pipe(words_lst);
	set_type(words_lst, globals);
	return (words_lst);
}
