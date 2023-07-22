/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:11:14 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/22 14:33:08 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

/**
 * @brief Get the values of the key passed as parameter.
 * 
 * @param current Environment variables list.
 * @param key Key to search.
 * @return char** Values of the key.
 */
static char	**search_key(t_env_var *current, char *key)
{
	int		stop;
	char	**values;

	stop = 0;
	values = 0;
	while (current && !stop)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			values = current->values;
			stop = 1;
		}
		current = current->next;
	}
	return (values);
}

/**
 * @brief Get the values of the key passed as parameter.
 * @details It handles the special keys "$" and "$?".
 * @param key Key to search.
 * @param lst Environment variables list.
 * @return char* The expanded values.
 */
char	*get_values(char *key, t_env_var **lst)
{
	char	**values;

	values = 0;
	if (!*lst || !key)
		return (0);
	if (ft_strcmp(key, "$") == 0)
		return (ft_strdup("$"));
	else if (ft_strcmp(key, "$?") == 0)
		return (ft_itoa(g_gbl.status));
	key = &key[1];
	values = search_key(*lst, key);
	return (values_to_str(values));
}
