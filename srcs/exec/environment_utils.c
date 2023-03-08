/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:05:29 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/03/08 11:41:07 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/exec.h"
/*
**	Create the beginning of the t_env_var chained list
*/
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
	env_var->key = malloc(sizeof(char) * first_equal);
	while (i < first_equal)
	{
		env_var->key[i] = env[i];
		i++;
	}
	if (env[first_equal + 1])
		env_var->values = ft_split(env + first_equal + 1, ':');
	else
		env_var->values = NULL;
	return (env_var);
}

/*old function with split{
	t_env_var	*env_var;
	char		**split;
	env_var = malloc(sizeof(t_env_var));
	if (!env_var)
		return (0);
	split = ft_split(env, '=');
	env_var->key = split[0];
	env_var->values = ft_split(split[1], ':');
	env_var->next = 0;
	return (env_var);
}*/

/*
**	Go to the end of the env_var chained list
*/
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

/*
**	add back to t_env_var chained list
*/
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

/*
**	Clear the env_var chained list
*/
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
