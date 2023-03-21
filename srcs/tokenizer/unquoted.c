/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquoted.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 20:49:02 by cbernot           #+#    #+#             */
/*   Updated: 2023/03/18 20:50:25 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	is_unquoted_double_chevron(char *line, int c_index)
{
	int	i;
	int	nb_single_quote;
	int	nb_double_quote;

	nb_double_quote = 0;
	nb_single_quote = 0;
	if (ft_strncmp(&line[c_index], "<<", 2) == 0 || ft_strncmp(&line[c_index], ">>", 2) == 0)
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
		else
			return (1);
	}
	else
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