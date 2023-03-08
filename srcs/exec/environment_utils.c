/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:05:29 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/03/08 11:05:57 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/exec.h"
/*
**	Create the beginning of the t_var_env chained list
*/
t_var_env	*var_env_new(char *env)
{
	t_var_env	*var_env;
	int	i;
	int	first_equal;
	var_env = malloc(sizeof(t_var_env));
	first_equal = 0;
	i = 0;
	while (env[first_equal]!= '=')
		first_equal++;
	var_env->key = malloc(sizeof(char) * i);
	while (i < first_equal)
	{
		var_env->key[i] = env[i];
		i++;
	}
	if (env[first_equal + 1])
		var_env->values = ft_split(env + first_equal + 1, ':');
	else
		var_env->values = NULL;
	return (var_env);
}

/*old function with split{
	t_var_env	*var_env;
	char		**split;
	var_env = malloc(sizeof(t_var_env));
	if (!var_env)
		return (0);
	split = ft_split(env, '=');
	var_env->key = split[0];
	var_env->values = ft_split(split[1], ':');
	var_env->next = 0;
	return (var_env);
}*/

/*
**	Go to the end of the var_env chained list
*/
t_var_env	*var_env_last(t_var_env *var_env)
{
	t_var_env	*current;

	current = var_env;
	if (var_env == 0)
		return (0);
	while (current->next)
		current = current->next;
	return (current);
}

/*
**	add back to t_var_env chained list
*/
void	var_env_add_back(t_var_env **var_env, t_var_env *new)
{
	t_var_env	*last;
	char		**split;

	if (*var_env == 0)
	{
		*var_env = new;
		return ;
	}
	last = var_env_last(*var_env);
	last->next = new;
}

/*
**	Clear the var_env chained list
*/
void	var_env_clear(t_var_env *var_env)
{
	int	i;
	t_var_env	*tmp;

	tmp = var_env;
	while (tmp)
	{
		tmp = var_env->next;
		free(var_env->key);
		i = 0;
		while (var_env->values[i])
		{
			free(var_env->values[i]);
			i++;
		}
		free(var_env->values);
		free(var_env);
		var_env = tmp;
	}
}
