/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:06:04 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/03/08 11:45:43 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/exec.h"

/*
**	Get values and keys from the initial environment where minishell starts
*/
t_env_var	*get_initial_env(char **env)
{
	int			i;
	t_env_var	*env_var;
	char		**split;

	i = 0;
	while (env[i])
	{
		printf("%d == %s\n", i, env[i]);
		env_var_add_back(&env_var, env_var_new(env[i]));
		i++;
	}
	return (env_var);
}

/*
**	Get the pointer to the correct variable we need
**	in the minishell environment
*/
t_env_var	*get_env_custom(char *key_to_find, t_env_var *env)
{
	int			flag;
	t_env_var	*cpy;

	cpy = env;
	flag = 0;
	while (cpy && flag == 0)
	{
		if (key_to_find == cpy->key)
		{
			flag = 1;
			break ;
		}
		cpy = cpy->next;
	}
	if (flag == 1)
		return (cpy);
	return (NULL);
}

/*
**	Main test -- WARNING : ERASE IT
*/
/*int	main()
{
	t_env_var	env;
	t_env_var	env2;
	t_env_var	env3;
	t_env_var	env4;
	t_env_var	*res;

	env.key = "dza";
	env.next = &env2;
	env2.key = "??";
	env2.next = &env3;
	env3.key = "PATH";
	env3.values = malloc(sizeof(char *));
	env3.values[0] = "Numero 0";
	env3.next = &env4;
	env4.key = "Nope";
	env4.next = NULL;
	res = get_env_custom("PATH", &env);
	printf ("%s\n", res->values[0]);
	free(env3.values);
	return 0;
}*/

int main(int argc, char **argv, char **env)
{
	t_env_var	*env_var;

	env_var = get_initial_env(env);
	//exec_env(env_var);
	//env_var_clear(env_var);
	return (0);
}