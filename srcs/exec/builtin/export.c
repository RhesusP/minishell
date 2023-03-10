/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:48:39 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/03/08 12:59:50 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/exec.h"

static int	exportable_variable(char *new_env)
{
	int	i;

	i = 0;
	while (new_env[i])
	{
		if (new_env[i] == '=')
			return (SUCCESS);
		i++;
	}
	//si la variable existe déjà, il faut la remplacer
	return (FAILURE);
}

void	exec_export(t_env_var *env_var, char *new_env)
{
	if (exportable_variable == SUCCESS)
		env_var_add_back(&env_var, env_var_new(new_env));
	else
		return ;
}
