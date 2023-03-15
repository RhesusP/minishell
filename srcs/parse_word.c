/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 01:46:22 by cbernot           #+#    #+#             */
/*   Updated: 2023/03/15 15:19:43 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	check_quotes_err(char *line)
{
	int	nb_single;
	int	nb_double;
	int	i;

	nb_single = 0;
	nb_double = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
			nb_single++;
		else if (line[i] == '"')
			nb_double++;
		i++;
	}
	if (nb_double % 2 != 0 || nb_single % 2 != 0)
		return (0);
	return (1);
}

int	is_metachar(char c)
{
	if (c == '|' || c == '(' || c == ')' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_unquoted_metachar(char *line, int c_index)
{
	int	i;
	int	nb_single_quote;
	int	nb_double_quote;

	nb_double_quote = 0;
	nb_single_quote = 0;
	if (!is_metachar(line[c_index]))
		return (0);
	i = 0;
	while (line[i] != '\0' && i < c_index)
	{
		if (line[i] == '"')
			nb_double_quote++;
		else if (line[i] == '\'')
			nb_single_quote++;
		i++;
	}
	if (!nb_double_quote && !nb_single_quote)
		return (1);
	if (nb_double_quote % 2 != 0 || nb_single_quote % 2 != 0)
		return (0);
	return (1);
}

int	is_unquoted(char *line, int c_index)
{
	int	i;
	int	nb_single_quote;
	int	nb_double_quote;

	nb_double_quote = 0;
	nb_single_quote = 0;
	i = 0;
	while (line[i] != '\0' && i < c_index)
	{
		if (line[i] == '"')
			nb_double_quote++;
		else if (line[i] == '\'')
			nb_single_quote++;
		i++;
	}
	if (!nb_double_quote && !nb_single_quote)
		return (1);
	if (nb_double_quote % 2 != 0 || nb_single_quote % 2 != 0)
		return (0);
	return (1);
}

int	is_unquoted_pipe(char *line, int c_index)
{
	int	i;
	int	nb_single_quote;
	int	nb_double_quote;

	nb_double_quote = 0;
	nb_single_quote = 0;
	if (line[c_index] != '|')
		return (0);
	i = 0;
	while (line[i] != '\0' && i < c_index)
	{
		if (line[i] == '"')
			nb_double_quote++;
		else if (line[i] == '\'')
			nb_single_quote++;
		i++;
	}
	if (!nb_double_quote && !nb_single_quote)
		return (1);
	if (nb_double_quote % 2 != 0 || nb_single_quote % 2 != 0)
		return (0);
	return (1);
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
		reparse = resplit(current->word);
		int	i = 0;
		while (reparse[i])
		{
			add_back_word(new_lst, create_word(reparse[i]));
			i++;
		}
		current = current->next;
	}
	free_word_lst(lst);
	return (new_lst);
}

void	parse_words(char *line, t_env_var *envs, t_env_var *globals)
{
	char	**tokens;
	t_word	**words_lst;
	t_word	*word;
	int		i;

	words_lst = malloc(sizeof(t_word *));
	if (!words_lst)
		return ;
	*words_lst = 0;
	tokens = ft_strtok(line, " \n\t");
	i = 0;
	while (tokens[i])
	{
		word = create_word(tokens[i]);
		add_back_word(words_lst, word);
		i++;
	}
	words_lst = detect_close_pipe(words_lst);
	set_type(words_lst, envs, globals);
}