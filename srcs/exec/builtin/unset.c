/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:00:37 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/05/10 10:51:56 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
// #include "../../../includes/exec.h"

void	exec_unset(t_env_var *env_var, char *unset_key)
{
	// t_env_var	*previous;

	// while (env_var && (env_var->key != unset_key))
	// {
	// 	previous = env_var;
	// 	env_var = env_var->next;
	// }
	// if (env_var != NULL)
	// {
	// 	previous->next = env_var->next;
	// printf("%s\n", env_var->key);
	// 	//free(env_var->key);
	// 	free(env_var->values);
	// 	//free_all(env_var->values);
	// printf("yo\n");
	// 	free(env_var);
	// }
}
