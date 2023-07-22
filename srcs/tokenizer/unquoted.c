/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquoted.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 20:49:02 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/21 16:06:26 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

/**
 * @brief Check if a char is an unquoted chevron (<< or >>)
 * 
 * @param line The string where the char is.
 * @param c_index The index of the char to analyze.
 * @return 1 if the char is an unquoted chevron, 0 otherwise.
 */
int	is_unquoted_double_chevron(char *line, int c_index)
{
	int	i;
	int	nb_single_quote;
	int	nb_double_quote;

	nb_double_quote = 0;
	nb_single_quote = 0;
	if (ft_strncmp(&line[c_index], "<<", 2) == 0 || \
		ft_strncmp(&line[c_index], ">>", 2) == 0)
	{
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
	return (0);
}

/**
 * @brief Check if a char is an unquoted metacharater.
 * 
 * @param line The string where the char is.
 * @param c_index The index of the char to analyze.
 * @return 1 if the char is an unquoted metacharater, 0 otherwise.
 */
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

/**
 * @brief Check if a char is unquoted.
 * 
 * @param line The string where the char is.
 * @param c_index The index of the char to analyze.
 * @return 1 if the char is unquoted, 0 otherwise.
 */
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

/**
 * @brief Check if a char is an unquoted pipe.
 * 
 * @param line The string where the char is.
 * @param c_index The index of the char to analyze.
 * @return 1 if the char is an unquoted pipe, 0 otherwise.
 */
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
