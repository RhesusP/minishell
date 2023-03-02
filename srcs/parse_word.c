/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 01:46:22 by cbernot           #+#    #+#             */
/*   Updated: 2023/03/02 15:57:32 by cbernot          ###   ########.fr       */
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
	if (c == ' ' || c == '\t' || c == '\n' || c == '|' || c == '&' || \
		c == ';' || c == '(' || c == ')' || c == '<' || c == '>')
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

int	ind_next_metachar(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && !is_metachar(line[i]))
		i++;
	return (i - 1);
}

void	debug_print_word(char *line, int start, int end)
{
	printf("word: ");
	while (start < end)
	{
		printf("%c", line[start]);
		start++;
	}
	printf("\n");
}

char	*get_next_token(char *line)
{
	int	i;
	int	ind_start;

	ind_start = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (is_metachar(line[i]) || line[i] == '"' || line[i] == '\'')
		{
			debug_print_word(line, ind_start, i);
			ind_start = i + 1;
			//printf("meta at %d\n", i);	
		}
		i++;
	}
	//printf("meta at %d\n", i);
	debug_print_word(line, ind_start, i);
	return (0);
}

int	get_single_quotes_word(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i + 1] != '\'')
		i++;
	return (i + 3);
}

int	get_double_quotes_word(t_word **words, char *line)
{
	t_word	*new;
	char	*str;
	int		i;

	i = 0;
	while (line[i] != '\0' && line[i] != '"')
		i++;
	str = ft_strndup(line, i);
	printf("word in 2 quotes: %s\n", str);
	return (i + 3);
}

void	handle_quotes(t_word **words, char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
			i += get_single_quotes_word(&line[i + 1]);
		if (line[i] == '"')
		{
			i += get_double_quotes_word(words, &line[i + 1]);
			printf("restart at:%s\n", &line[i]);
		}
		else
			i++;
	}
}

void	tokenize(t_word **words, char *line)
{
	//handle_quotes(words, line);
	int		i;
	int		start;
	char	*token;
	t_word	*word;
	t_type	type;

	i = 0;
	while (is_unquoted_metachar(line, i))
		i++;
	start = i;
	printf("I start at %s\n", &line[start]);
	while (line[i] != '\0')
	{
		if (is_unquoted_metachar(line, i))
		{
			token = ft_strndup(&line[start], i - start);
			type = ARG;
			word = create_word(token, type);
			add_back_word(words, word);
			printf("token: %s\n", token);
			start = i + 1;
		}
		i++;
	}
	token = ft_strndup(&line[start], i - start);
	printf("token: %s\n", token);
	display_words(words);
	//get_next_token(line);
}

/*
t_word	**parse_words(char *line)
{
	t_word	**words;

	words = malloc(sizeof(t_word *));
	if (!words)
		return (0);
	*words = 0;
	if (!check_quotes_err(line))
		return (0);
	// tokenyze then symplify
	tokenize(words, line);
}
*/

int	count_cmd(char *line)
{
	int	i;
	int	nb_pipes;

	if (ft_strlen(line) == 0)
		return (0);
	i = 0;
	nb_pipes = 0;
	while (line[i] != '\0' && is_unquoted_metachar(line, i))
		i++;
	while (line[i] != '\0')
	{
		if (is_unquoted_pipe(line, i))
			nb_pipes++;
		i++;
	}
	return (nb_pipes + 1);
}

t_command	get_next_command(char *line, int *ret)
{
	t_command	cmd;
	int			i;
	int			start;
	int			len;
	t_word		**words;
	char		*word;

	printf("analyzed line: %s\n", line);
	words = malloc(sizeof(t_word *));
	if (!words)
		printf("ta grand mere le malloc a(free)que\n");	//TODO malloc to check
	*words = 0;
	i = 0;
	len = 1;
	start = i;
	while (line[i] != '\0' && !is_unquoted_pipe(line, i))
	{
		if (is_unquoted_metachar(line, i))
		{
			word = ft_strndup(&line[start], len);
			printf("word detected: %s (%ld)\n", word, ft_strlen(word));
			if (ft_strlen(word) == 1 && is_unquoted_metachar(libe))
			add_back_word(words, create_word(word, 1));
			len = 1;
			start = i + 1;
			i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	*ret = start + len;
	add_back_word(words, create_word(ft_strndup(&line[start], len), 1));
	display_words(words);
	cmd.words = words;
	return (cmd);
}

void	parse_words(char *line)
{
	t_command	*commands;
	int			nb_cmd;
	int			i;
	int			start;

	nb_cmd = count_cmd(line);
	printf("there is %d commands\n", nb_cmd);
	commands = malloc(sizeof(t_command) * nb_cmd);
	if (!commands)
	{
		printf("error while allocating space\n");
		return ;
	}
	commands[0] = get_next_command(line, &start);
	printf("next: %s\n", &line[start]);
	commands[1] = get_next_command(&line[start], &start);
}