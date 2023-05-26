/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:42:54 by cbernot           #+#    #+#             */
/*   Updated: 2023/05/26 09:45:11 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

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
	int		i;

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
	var->key = get_var_key(line);
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
