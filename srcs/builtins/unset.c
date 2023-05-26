/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:00:37 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/05/24 13:51:58 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_single_var(t_env_var *delete)
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

t_env_var	*get_prev(t_env_var **env, char *key)
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

void	delete_existing_key(t_env_var **env, char *key)
{
	t_env_var	*prev;
	t_env_var	*delete;
	int			i;

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

void	ft_unset(t_word **lst, t_env_var **env, t_env_var **global)
{
	t_word		*current;

	if (!*lst)
		return ;
	current = *lst;
	while (current && current->type != ARG)
		current = current->next;
	while (current && current->type == ARG)
	{
		if (is_already_here(env, current->word))
			delete_existing_key(env, current->word);
		if (is_already_here(global, current->word))
			delete_existing_key(global, current->word);
		current = current->next;
	}
}
