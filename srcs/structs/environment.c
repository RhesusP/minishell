/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:06:04 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/07/21 16:40:27 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
*	@brief Get the pointer to the correct variable we need
*	in the minishell environment
**/
t_env_var	*get_env_custom(char *key_to_find, t_env_var *env)
{
	int			flag;
	t_env_var	*cpy;

	cpy = env;
	flag = 0;
	while (cpy && flag == 0)
	{
		if (ft_strcmp(key_to_find, cpy->key) == SUCCESS)
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
