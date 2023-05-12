/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:14:56 by cbernot           #+#    #+#             */
/*   Updated: 2023/05/12 15:55:58 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	free_env(t_env_var *env)
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
		while (current->values[i])
		{
			free(current->values[i]);
			i++;
		}
		free(current->values);
		current = next;
	}
}

void	ft_free(t_env_var *env, t_env_var *global)
{
	free_env(env);
	free(env);
	// free_env(*global);
	rl_clear_history();
}