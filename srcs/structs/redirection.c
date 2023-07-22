/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:10:12 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/21 16:46:05 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

/**
 * @brief Create a redir object
 * @details a redir object is a pair of type (RI, RO, ARO, HE) and filepath.
 * @param type RI, RO, ARO, HE
 * @param path path to the file
 * @return t_redir* 
 */
t_redir	*create_redir(t_type type, char *path)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (0);
	redir->type = type;
	redir->filepath = ft_strdup(path);
	redir->next = 0;
	return (redir);
}

/**
 * @brief Get the last redir object of the chained list.
 * 
 * @param lst 
 * @return t_redir* The last one.
 */
static t_redir	*get_last_redir(t_redir *lst)
{
	t_redir	*current;

	if (!lst)
		return (0);
	current = lst;
	while (current->next)
		current = current->next;
	return (current);
}

/**
 * @brief Add a redirection to the end of a chained list.
 * 
 * @param lst Chained list.
 * @param new Element to add. 
 */
void	add_back_redir(t_redir **lst, t_redir *new)
{
	t_redir	*last;

	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	last = get_last_redir(*lst);
	last->next = new;
}

/**
 * @brief Free a redirection chained list.
 * 
 * @param redir 
 */
void	free_redir(t_redir **redir)
{
	t_redir	*current;
	t_redir	*next;

	current = *redir;
	while (current)
	{
		next = current->next;
		free(current->filepath);
		free(current);
		current = next;
	}
	free(redir);
}

/**
 * @brief Checks if a word is a redirection (>, >>, <, <<)
 * 
 * @param word 
 * @return 1 if the word is a redirection, 0 otherwise.
 */
int	type_is_redir(t_word *word)
{
	if (word->type == RI || \
		word->type == RO || \
		word->type == ARO || \
		word->type == HE)
		return (1);
	return (0);
}
