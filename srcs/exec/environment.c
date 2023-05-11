/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:06:04 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/05/11 09:35:14 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// #include "../../includes/exec.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (FAILURE);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

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
