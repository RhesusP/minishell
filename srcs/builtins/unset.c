/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:00:37 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/07/22 14:38:32 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Delete the environment variable passed as parameter.
 * 
 * @param delete
 */
static void	delete_single_var(t_env_var *delete)
{
	int	i;

	free(delete->key);
	i = 0;
	while (delete->values && delete->values[i])
	{
		free(delete->values[i]);
		i++;
	}
	free(delete->values);
	free(delete);
}

/**
 * @brief Get the element before the key element in the chained list.
 * 
 * @param env Environment variables list.
 * @param key Key to search.
 * @return t_env_var* Previous element.
 */
static t_env_var	*get_prev(t_env_var **env, char *key)
{
	t_env_var	*current;
	t_env_var	*last;

	if (!env || !*env)
		return (0);
	current = *env;
	if (ft_strcmp(current->key, key) == 0)
		return (0);
	while (current)
	{
		if (current->next && ft_strcmp(current->next->key, key) == 0)
			return (current);
		last = current;
		current = current->next;
	}
	return (last);
}

/**
 * @brief Delete the key passed as parameter from the environment variables list.
 * 
 * @param env Environment variables list.
 * @param key Key of the environment variable to delete.
 */
static void	delete_existing_key(t_env_var **env, char *key)
{
	t_env_var	*prev;
	t_env_var	*delete;

	prev = get_prev(env, key);
	if (!prev)
	{
		delete = *env;
		*env = delete->next;
		delete_single_var(delete);
	}
	else
	{
		delete = prev->next;
		prev->next = delete->next;
		delete_single_var(delete);
	}
}

/**
 * @brief Unset builtin. Delete the key passed as parameter from 
 * the environment variables list.
 * @details If the key is not found or if there is not argument,
 * nothing happens.
 * @param lst Sub-command to execute.
 * @param env Environment variables list.
 */
void	ft_unset(t_word **lst, t_env_var **env)
{
	t_word		*current;

	if (!*lst)
		return ;
	current = *lst;
	g_gbl.status = 0;
	while (current && current->type != ARG)
		current = current->next;
	while (current && current->type == ARG)
	{
		if (is_already_here(env, current->word))
			delete_existing_key(env, current->word);
		current = current->next;
	}
}
