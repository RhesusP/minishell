/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmeen <svanmeen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:42:54 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/19 12:20:26 by svanmeen         ###   ########.fr       */
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
