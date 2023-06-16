/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:12:54 by cbernot           #+#    #+#             */
/*   Updated: 2023/06/16 11:05:36 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

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
