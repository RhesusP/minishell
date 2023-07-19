/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:05:29 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/07/19 09:08:08 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
*	@brief Go to the end of the env_var chained list
**/
static t_env_var	*env_var_last(t_env_var *env_var)
{
	t_env_var	*current;

	current = env_var;
	if (env_var == 0)
		return (0);
	while (current->next)
		current = current->next;
	return (current);
}

/**
*	@brief back to t_env_var chained list
**/
void	env_var_add_back(t_env_var **env_var, t_env_var *new)
{
	t_env_var	*last;

	if (*env_var == 0)
	{
		*env_var = new;
		return ;
	}
	last = env_var_last(*env_var);
	last->next = new;
}

/**
*	@brief Clear the env_var chained list
**/
void	env_var_clear(t_env_var *env_var)
{
	int			i;
	t_env_var	*tmp;

	tmp = env_var;
	while (tmp)
	{
		tmp = env_var->next;
		free(env_var->key);
		i = 0;
		while (env_var->values[i])
		{
			free(env_var->values[i]);
			i++;
		}
		free(env_var->values);
		free(env_var);
		env_var = tmp;
	}
}

char	*get_home(t_env_var *env)
{
	t_env_var	*current;

	if (!env)
		return (0);
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, "HOME") == 0)
		{
			if (current->values && current->values[0])
				return (current->values[0]);
			else
				return ("");
		}
		current = current->next;
	}
	return (0);
}
