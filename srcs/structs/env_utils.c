/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:18:46 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/21 11:35:27 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	is_already_here(t_env_var **env, char *key)
{
	t_env_var	*current;

	if (!env ||!*env)
		return (0);
	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}
