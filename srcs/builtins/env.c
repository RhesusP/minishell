/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:57:57 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/07/22 14:44:52 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Check if the command have an argument.
 * 
 * @param lst Sub-command to execute.
 * @return 1 if the command have an argument, 0 otherwise.
 */
static int	cmd_have_arg(t_word **lst)
{
	t_word	*current;

	current = *lst;
	while (current)
	{
		if (current->type == ARG)
			return (1);
		current = current->next;
	}
	return (0);
}

/**
 * @brief Print the environment variables list.
 * @details If the command have an argument, it prints an error message.
 * @param lst Sub-command to execute.
 * @param env Environment variables list.
 */
void	ft_env(t_word **lst, t_env_var *env)
{
	t_env_var	*current;
	int			i;

	if (cmd_have_arg(lst))
	{
		perror("env command does not take any argument.");
		return ;
	}
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
