/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:18:46 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/19 09:03:51 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

/**
 * @brief Get only the key from the cmd KEY=value
 * @return Return a char * containing the KEY
*/
static char	*get_word_key(char *word)
{
	int		i;
	char	*ret;

	i = 0;
	while (word[i] != '=')
		i++;
	ret = calloc(i + 1, sizeof(char));
	i = 0;
	while (word[i] != '=')
	{
		ret[i] = word[i];
		i++;
	}
	return (ret);
}

/**
 * @brief change the value of the global variable in the structure to actualize
 * it
*/
static void	change_value(t_env_var *current, char *word)
{
	int	i;

	i = 0;
	while (word[i] != '=')
		i++;
	i++;
	current->values = malloc(sizeof(char *) * 2);
	current->values[0] = ft_strdup(word + i);
	current->values[1] = NULL;
}

/**
 * @brief Check if the global variable already exists and actualize it if so
 * @return SUCCESS if a variable was actualized // 
 * @return FAILURE is not variable was actualized
*/
int	actualize_global_var(t_env_var **globals, char *word)
{
	t_env_var	*current;
	char		*word_key;

	current = *globals;
	word_key = get_word_key(word);
	while (current)
	{
		if (ft_strcmp(current->key, word_key) == 0)
		{
			free_all(current->values);
			change_value(current, word);
			free(word_key);
			return (SUCCESS);
		}
		current = current->next;
	}
	free(word_key);
	return (FAILURE);
}

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
