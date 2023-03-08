/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:57:57 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/03/08 12:00:32 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/exec.h"

/*
**	Print the environment on the terminal
*/
void	exec_env(t_env_var *env_var)
{
	int	i;

	i = 0;
	while (env_var)
	{
		printf("%s", env_var->key);
		printf("=");
		i = 0;
		while (env_var->values[i])
		{
			if (i > 0)
				printf(":");
			printf("%s",env_var->values[i]);
			i++;
		}
		printf("\n");
		env_var = env_var->next;
	}
}
