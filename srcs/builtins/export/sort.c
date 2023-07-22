/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:24:06 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/22 18:31:00 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief Copy an env_var structure
 * @details The copy is a deep copy, it copies the key and the values,
 * but not the next pointer
 * @param env The env_var to copy
 * @return t_env_var* The copy
 */
static t_env_var	*copy_env_var(t_env_var *env)
{
	t_env_var	*copy;
	int			i;

	copy = malloc(sizeof(t_env_var));
	if (!copy)
		return (NULL);
	copy->key = ft_strdup(env->key);
	i = 0;
	while (env->values[i])
		i++;
	copy->values = malloc(sizeof(char *) * (i + 1));
	if (!copy->values)
		return (NULL);
	i = 0;
	while (env->values[i])
	{
		copy->values[i] = ft_strdup(env->values[i]);
		i++;
	}
	copy->values[i] = NULL;
	copy->next = NULL;
	return (copy);
}

/**
 * @brief Insert an element in a sorted list
 * @details The list is sorted by key, in alphabetical order. It uses
 * insertion sorting
 * @param sorted_list 
 * @param element 
 */
static void	insert_element(t_env_var **sorted_list, t_env_var *element)
{
	t_env_var	*current;

	if (!*sorted_list || strcmp(element->key, (*sorted_list)->key) < 0)
	{
		element->next = *sorted_list;
		*sorted_list = element;
		return ;
	}
	current = *sorted_list;
	while (current->next != NULL && strcmp(element->key, \
		current->next->key) >= 0)
		current = current->next;
	element->next = current->next;
	current->next = element;
}

/**
 * @brief Create a copy of the env list, sorted by key
 * 
 * @param env List to copy and sort.
 * @return t_env_var* The sorted copy
 */
t_env_var	*create_sorted_env_var(t_env_var *env)
{
	t_env_var	*sorted_list;
	t_env_var	*current;
	t_env_var	*tmp;

	sorted_list = NULL;
	current = env;
	while (current)
	{
		tmp = copy_env_var(current);
		insert_element(&sorted_list, tmp);
		current = current->next;
	}
	return (sorted_list);
}
