/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:00:37 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/03/08 13:12:22 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/exec.h"

void	exec_unset(t_env_var *env_var, char *unset_key)
{
	t_env_var	*previous;

	while (env_var && (env_var->key != unset_key))
	{
		previous = env_var;
		env_var = env_var->next;
	}
	if (env_var != NULL)
	{
		previous->next = env_var->next;
	printf("%s\n", env_var->key);
		//free(env_var->key);
		free(env_var->values);
		//free_all(env_var->values);
	printf("yo\n");
		free(env_var);
	}
}

// MAINT TEST -- WARNING TO ERASE
int main()
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
	exec_unset(env1, "ENV2");
	while (env1)
	{
		printf("%s=%s\n", env1->key, env1->values[0]);
		env1 = env1->next;
	}
	env_var_clear(env1);
	return 0;
}
