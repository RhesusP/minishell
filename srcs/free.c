/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:14:56 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/21 11:28:23 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

static void	free_env(t_env_var *env)
{
	t_env_var	*current;
	t_env_var	*next;
	int			i;

	if (!env)
		return ;
	current = env;
	while (current)
	{
		next = current->next;
		free(current->key);
		i = 0;
		while (current->values && current->values[i])
		{
			free(current->values[i]);
			i++;
		}
		free(current->values);
		free(current);
		current = next;
	}
}

void	ft_free(t_env_var *env)
{
	free_env(env);
	rl_clear_history();
}

void	free_word_lst(t_word **lst)
{
	t_word	*current;
	t_word	*next;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		free(current->word);
		free(current);
		current = next;
	}
	free(lst);
}
