/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:18:46 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/21 16:39:44 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

/**
 * @brief Checks if a key is already in the environment.
 * 
 * @param env Environment list to check
 * @param key Key to found.
 * @return 1 if the key is already in the environment, 0 otherwise.
 */
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

/**
 * @brief Get the size of the environment chained list.
 * 
 * @param env 
 * @return int 
 */
static int	get_env_size(t_env_var *env)
{
	t_env_var	*current;
	int			size;

	size = 0;
	if (!env)
		return (0);
	current = env;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}

/**
 * @brief Create a string with the key and the values of an environment
 * variable.
 * 
 * @param key Key of the environment variable.
 * @param tab Values of the environment variable.
 * @return char* Allocated (with malloc(3)) string.
 */
static char	*join_env_values(char *key, char **tab)
{
	char	*res;
	char	*temp;
	int		i;

	res = ft_strjoin(key, "=");
	i = 0;
	while (tab[i])
	{
		temp = ft_strjoin(res, tab[i]);
		free(res);
		res = ft_strdup(temp);
		free(temp);
		if (tab[i + 1])
		{
			temp = ft_strjoin(res, ":");
			free(res);
			res = ft_strdup(temp);
			free(temp);
		}
		i++;
	}
	return (res);
}

/**
 * @brief Convert an environment chained list to a tab of strings.
 * 
 * @param env 
 * @return char** 
 */
char	**env_to_tab(t_env_var *env)
{
	t_env_var	*current;
	char		**tab;
	int			cell;

	if (!env)
		return (0);
	tab = malloc(sizeof(char *) * (get_env_size(env) + 1));
	if (!tab)
		return (0);
	current = env;
	cell = 0;
	while (current)
	{
		tab[cell] = join_env_values(current->key, current->values);
		cell++;
		current = current->next;
	}
	tab[cell] = 0;
	return (tab);
}

/**
 * @brief Get the $HOME environment variable.
 * 
 * @param env 
 * @return char* The first value of $HOME
 */
char	*get_home(t_env_var *env)
{
	t_env_var	*current;

	if (!env)
		return (0);
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, "HOME") == 0)
		{
			if (current->values && current->values[0])
				return (current->values[0]);
			else
				return ("");
		}
		current = current->next;
	}
	return (0);
}
