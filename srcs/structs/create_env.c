/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:42:54 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/22 16:56:17 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

/**
 * @brief Get the key of an environment variable.
 * @details For example, for the environeent variable
 * `PATH=/bin:/usr/bin:/usr/local/bin`, key is `PATH`.
 * @param str 
 * @return char* 
 */
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

/**
 * @brief Get the values of an environment variable.
 * @details Split the values with ':' as a delimiter. For example, for
 * the environeent variable `PATH=/bin:/usr/bin:/usr/local/bin`, values
 * are `["/bin", "/usr/bin", "/usr/local/bin"]`.
 * @param str 
 * @return char** 
 */
char	**get_var_values(char *str)
{
	char	**values;
	int		i;
	char	*tmp;
	char	*tmp1;

	i = 0;
	while (str[i] != '=')
		i++;
	values = ft_split(&str[i + 1], ':');
	if (str[i + 1] == ':')
	{
		tmp = ft_strjoin(":", values[0]);
		free(values[0]);
		values[0] = tmp;
	}
	if (str[ft_strlen(str) - 1] == ':')
	{
		i = 0;
		while (values[i])
			i++;
		tmp1 = ft_strjoin(values[i - 1], ":");
		free(values[i - 1]);
		values[i - 1] = tmp1;
	}
	return (values);
}

/**
 * @brief Create a new environment variable object.
 * 
 * @param line Line of the environment file
 * (ex: `PATH=/bin:/usr/bin:/usr/local/bin`).
 * @return t_env_var* Allocated with malloc(3) environment variable object.
 */
t_env_var	*create_env_var(char *line)
{
	t_env_var	*var;

	var = malloc(sizeof(t_env_var));
	if (!var)
		return (0);
	var->key = get_var_key(line);
	var->values = get_var_values(line);
	var->next = 0;
	return (var);
}

/**
 * @brief Get the last object from the environment list.
 * 
 * @param lst 
 * @return t_env_var* 
 */
static t_env_var	*get_last_env_var(t_env_var *lst)
{
	t_env_var	*current;

	if (!lst)
		return (0);
	current = lst;
	while (current->next)
		current = current->next;
	return (current);
}

/**
 * @brief Add a new environment variable at the end of the list.
 * 
 * @param lst 
 * @param new 
 */
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
