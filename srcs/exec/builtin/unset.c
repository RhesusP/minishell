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

	while (env_var && env_var->key != unset_key)
	{
		previous = env_var;
		env_var = env_var->next;
	}
	if (env_var)
	{
		previous->next = env_var->next;
		free(env_var->key);
		free_all(env_var->values);
	}
}
