/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:34:17 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/22 16:56:34 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Get the length of the command with args.
 * @details Length is the number of CMD and ARG in the chained list.
 * @param lst 
 * @return int 
 */
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
 * @brief Count the number of pipes in the chained list.
 * @details Useful to split the command into subcommands.
 * @param word 
 * @return int 
 */
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

/**
 * @brief Copy a string array.
 * 
 * @param tab 
 * @return char** 
 */
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
 * @brief Convert a word chained list into a string array.
 * @details Convert only CMD and ARG types into a string array.
 * This function is useful for execve().
 * @param lst 
 * @return char** 
 */
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

/**
 * @brief Unlink temporary here document files and free them.
 * 
 * @param to_free 
 * @param nb_pipes Number of pipes in the current command.
 */
void	unlink_he_files(t_to_free *to_free, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes + 2)
	{
		if (to_free->he_files[i])
			unlink(to_free->he_files[i]);
		free(to_free->he_files[i]);
		i++;
	}
	free(to_free->he_files);
}
