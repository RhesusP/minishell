/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:05:29 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/04/13 12:03:33 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/exec.h"
/**
*	@brief Create the beginning of the t_env_var chained list
**/
t_env_var	*env_var_new(char *env)
{
	t_env_var	*env_var;
	int	i;
	int	first_equal;

	env_var = malloc(sizeof(t_env_var));
	first_equal = 0;
	i = 0;
	while (env[first_equal]!= '=')
		first_equal++;
	env_var->key = calloc((first_equal + 1), sizeof(char));
	while (i < first_equal)
	{
		env_var->key[i] = env[i];
		i++;
	}
	if (env[first_equal + 1])
		env_var->values = ft_split(env + first_equal + 1, ':');
	else
	{
		env_var->values = malloc(sizeof(char *));
		env_var->values[0] = malloc(sizeof(char));
		env_var->values[0] = '\0';
	}
	return (env_var);
}

/**
*	@brief Go to the end of the env_var chained list
**/
t_env_var	*env_var_last(t_env_var *env_var)
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
	char		**split;

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
	int	i;
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
	while (current && ft_strcmp(current->key, "HOME") != 0)
		current = current->next;
	return (current->values[0]);
}