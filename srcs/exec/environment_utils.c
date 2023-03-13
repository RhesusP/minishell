/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:05:29 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/03/08 14:03:00 by tbarde-c         ###   ########.fr       */
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

//MAIN TEST -- WARNING TO ERASE
/*int main()
{
	t_env_var *env1;
	t_env_var *env2;
	t_env_var *env3;

	env1 = malloc(sizeof(t_env_var));
	env2 = malloc(sizeof(t_env_var));
	env3 = malloc(sizeof(t_env_var));
	env1->values = malloc(sizeof(char *));
	env2->values = malloc(sizeof(char *));
	env3->values = malloc(sizeof(char *));

	env1->key = "ENV1";
	env1->values[0] = "1st value";
	env2->key = "ENV2";
	env2->values[0] = "2nd value";
	env3->key = "ENV3";
	env3->values[0] = "3rd value";

	env1->next = env2;
	env2->next = env3;
	env3->next = NULL;
	env_var_add_back(&env1, env_var_new("ENV4=4th Value"));
	while (env1)
	{
		printf("%s=%s\n", env1->key, env1->values[0]);
		env1 = env1->next;
	}
	env_var_clear(env1);
	return 0;
}*/
