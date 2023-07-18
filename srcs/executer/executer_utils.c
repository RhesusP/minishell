/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:34:17 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/17 16:50:29 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
*	@brief Get the number of args for the execution of one programm
**/
static int	get_exec_len(t_word **lst)
{
	int		len;
	t_word	*current;

	len = 0;
	current = *lst;
	while (current)
	{
		if (current->type == CMD || current->type == ARG)
			len++;
		current = current->next;
	}
	return (len);
}

/**
 * @brief Counts the number of pipe that were parsed
 * @return Number of pipes counted
**/
int	count_pipes(t_word **word)
{
	int		pipe_nbr;
	t_word	*current;

	pipe_nbr = 0;
	if (!*word)
		return (0);
	current = *word;
	while (current)
	{
		if (current->type == PIPE)
			pipe_nbr++;
		current = current->next;
	}
	return (pipe_nbr);
}

char	**copy_string_array(char **tab)
{
	int		len;
	int		i;
	char	**res;

	if (!tab)
		return (0);
	len = 0;
	while (tab[len])
		len++;
	res = malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (0);
	i = 0;
	while (tab[i] != 0)
	{
		res[i] = ft_strdup(tab[i]);
		i++;
	}
	res[i] = 0;
	return (res);
}

/**
*	@brief Get the command with args from the parser into a char **
*	Then we'll be able to pass the full command to execve()
**/
char	**lst_to_string(t_word **lst)
{
	char	**tab;
	int		len;
	t_word	*current;
	int		i;

	i = 0;
	len = get_exec_len(lst);
	if (len == 0)
		return (0);
	tab = malloc(sizeof(t_word *) * (len + 1));
	if (!tab)
		return (0);
	current = *lst;
	while (current)
	{
		if (current->type == CMD || current->type == ARG)
		{
			tab[i] = ft_strdup(current->word);
			i++;
		}
		current = current->next;
	}
	tab[i] = 0;
	return (tab);
}
