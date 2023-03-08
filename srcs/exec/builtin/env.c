/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:57:57 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/03/08 10:59:06 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/exec.h"

/*
**	Print the environment on the terminal
*/
void	exec_env(t_var_env *var_env)
{
	int	i;

	i = 0;
	while (var_env)
	{
		printf("%s", var_env->key);
		printf("=");
		i = 0;
		while (var_env->values[i])
		{
			if (i > 0)
				printf(":");
			printf("%s",var_env->values[i]);
			i++;
		}
		printf("\n");
		var_env = var_env->next;
	}
}