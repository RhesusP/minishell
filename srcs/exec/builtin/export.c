/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:48:39 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/04/16 17:49:52 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/exec.h"

t_env_var	*is_var_exists(t_env_var *env, char *search)
{
	t_env_var	*current;

	if (!env)
		return (0);
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, search) == 0)
			return (current);
		current = current->next;
	}
	return (0);
}

void	ft_export(t_word **lst, t_env_var *env)
{
	// TODO export alone
	display_words(lst);
	t_word	*current;
	t_env_var	*var;

	if (!*lst)
		return ;
	current = *lst;
	while (current && current->type != ARG)
		current = current->next;
	while (current && current->type == ARG)
	{
		var = is_var_exists(env, get_var_key(current->word));
		if (!var)
			add_back_env_var(&env, create_env_var(current->word));
		else
		{
			free(var->values);
			var->values = get_var_values(current->word);
		}
		current = current->next;
	}
}

// MAINT TEST -- WARNING TO ERASE
// int main()
// {
// 	t_env_var *env1;
// 	t_env_var *env2;
// 	t_env_var *env3;

// 	env1 = malloc(sizeof(t_env_var));
// 	env2 = malloc(sizeof(t_env_var));
// 	env3 = malloc(sizeof(t_env_var));
// 	env1->values = malloc(sizeof(char *));
// 	env2->values = malloc(sizeof(char *));
// 	env3->values = malloc(sizeof(char *));

// 	env1->key = "ENV1";
// 	env1->values[0] = "1st value";
// 	env2->key = "ENV2";
// 	env2->values[0] = "2nd value";
// 	env3->key = "ENV3";
// 	env3->values[0] = "3rd value";

// 	env1->next = env2;
// 	env2->next = env3;
// 	env3->next = NULL;
// 	exec_export(env1, "ENV1=redefinition");
// 	while (env1)
// 	{
// 		printf("%s=%s\n", env1->key, env1->values[0]);
// 		env1 = env1->next;
// 	}
// 	env_var_clear(env1);
// 	return 0;
// }
