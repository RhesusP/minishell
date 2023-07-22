/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:51:31 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/22 14:55:08 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief Get the $OLDPWD environment variable.
 * 
 * @param env 
 * @return t_env_var* 
 */
t_env_var	*get_old_pwd(t_env_var *env)
{
	t_env_var	*current;

	if (!env)
		return (0);
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, "OLDPWD") == 0)
			return (current);
		current = current->next;
	}
	return (0);
}

/**
 * @brief Get the $PWD environment variable.
 * 
 * @param env 
 * @return t_env_var* 
 */
t_env_var	*get_pwd(t_env_var *env)
{
	t_env_var	*current;

	if (!env)
		return (0);
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, "PWD") == 0)
			return (current);
		current = current->next;
	}
	return (0);
}

/**
 * @brief Get the number of directories in a path.
 * @details Example: "/home/user" -> 3.
 * @param path 
 * @return int 
 */
int	count_dir(char *path)
{
	int	i;
	int	reset;
	int	nb;

	reset = 1;
	nb = 0;
	i = 0;
	while (path[i] != '\0')
	{
		if (path[i] != '/' && reset)
		{
			nb++;
			reset = 0;
		}
		else if (path[i] == '/')
			reset = 1;
		i++;
	}
	return (nb);
}
