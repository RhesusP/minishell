/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 01:46:22 by cbernot           #+#    #+#             */
/*   Updated: 2023/05/17 10:16:31 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	is_metachar(char c)
{
	if (c == '|' || c == '(' || c == ')' || c == '<' || c == '>')
		return (1);
	return (0);
}

t_word	**detect_close_pipe(t_word **lst)
{
	t_word	*current;
	t_word	**new_lst;
	char	**reparse;

	if (!*lst)
		return (0);
	new_lst = malloc(sizeof(t_word *));
	if (!new_lst)
		return (0);
	*new_lst = 0;
	current = *lst;
	while (current)
	{
		if (ft_strcmp(current->word, "<<") == 0 || ft_strcmp(current->word, ">>") == 0)
		{
			add_back_word(new_lst, create_word(current->word));
			current = current->next;
		}
		else
		{
			reparse = resplit(current->word);
			int	i = 0;
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

			current = current->next;
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

