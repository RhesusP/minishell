/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:18:46 by cbernot           #+#    #+#             */
/*   Updated: 2023/05/12 14:47:05 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*get_var_key(char *str)
{
	char	*key;
	int		size;

	size = 0;
	while (str[size] != '=')
		size++;
	key = ft_strndup(str, size);
	return (key);
}

char	**get_var_values(char *str)
{
	char	**values;
	int	i;
	
	i = 0;
	while (str[i] != '=')
		i++;
	values = ft_split(&str[i + 1], ':');
	return (values);
}

t_env_var	*create_env_var(char *line)
{
	t_env_var	*var;

	var = malloc(sizeof(t_env_var));
	if (!var)
		return (0);
	var->key = get_var_key(line);	//handle fail
	var->values = get_var_values(line);
	var->next = 0;
	return (var);
}

t_env_var	*get_last_env_var(t_env_var *lst)
{
	t_env_var	*current;

	if (!lst)
		return (0);
	current = lst;
	while (current->next)
		current = current->next;
	return (current);
}

void	add_back_env_var(t_env_var **lst, t_env_var *new)
{
	t_env_var	*last;

	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	last = get_last_env_var(*lst);
	last->next = new;
}



/**
 * @brief Get only the key from the cmd KEY=value
 * @return Return a char * containing the KEY
*/
char	*get_word_key(char *word)
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
 * @brief change the value of the global variable in the structure to actualize it
*/
void	change_value(t_env_var *current, char *word)
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
	char		*temp;
	char		*word_key;

	current = *globals;
	word_key = get_word_key(word);
	while (current)
	{
		if (ft_strcmp(current->key, word_key) == 0)
		{
			//printf("ENTERED\n");
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

/**
 * @brief free a t_env_var
*/
void	free_env_var(t_env_var *env_var)
{
	t_env_var	*tmp;

	while (env_var)
	{
		tmp = env_var->next;
		free(env_var->key);
		free_all(env_var->values);
		free(env_var);
		env_var = tmp;
	}
}