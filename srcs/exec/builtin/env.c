/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:57:57 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/04/07 11:34:38 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/exec.h"

void	ft_env(t_env_var *env)
{
	t_env_var	*current;
	int			i;

	current = env;
	while (current)
	{
		printf("%s=", current->key);
		i = 0;
		while (current->values[i])
		{
			if (current->values[i + 1])
				printf("%s:", current->values[i]);
			else
					printf("%s", current->values[i]);
			i++;
		}
		printf("\n");
		current = current->next;
	}
}