/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:05:29 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/05/21 15:01:02 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
*	@brief Go to the end of the env_var chained list
**/
t_env_var	*env_var_last(t_env_var *env_var)
{
	t_env_var	*current;

	current = env_var;
	if (env_var == 0)
		return (0);
	while (current->next)
		current = current->next;
	return (current);
}

/**
*	@brief back to t_env_var chained list
**/
void	env_var_add_back(t_env_var **env_var, t_env_var *new)
{
	t_env_var	*last;
	char		**split;

	if (*env_var == 0)
	{
		*env_var = new;
		return ;
	}
	last = env_var_last(*env_var);
	last->next = new;
}

/**
*	@brief Clear the env_var chained list
**/
void	env_var_clear(t_env_var *env_var)
{
	int	i;
	t_env_var	*tmp;

	tmp = env_var;
	while (tmp)
	{
		tmp = env_var->next;
		free(env_var->key);
		i = 0;
		while (env_var->values[i])
		{
			free(env_var->values[i]);
			i++;
		}
		free(env_var->values);
		free(env_var);
		env_var = tmp;
	}
}

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

int	get_env_size(t_env_var *env)
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

char	*join_env_values(char *key, char **tab)
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