/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:57:55 by cbernot           #+#    #+#             */
/*   Updated: 2023/06/16 10:13:08 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static void	update_shlvl(t_env_var *env)
{
	t_env_var	*current;
	int			old_lvl;

	if (!env)
		return ;
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, "SHLVL") == 0)
		{
			old_lvl = ft_atoi(current->values[0]);
			free(current->values[0]);
			current->values[0] = ft_itoa(old_lvl + 1);
			return ;
		}
		current = current->next;
	}
}

t_env_var	*get_environment(char **env)
{
	int			i;
	t_env_var	*res;
	t_env_var	*new_var;

	res = NULL;
	i = 0;
	while (env[i])
	{
		new_var = create_env_var(env[i]);
		add_back_env_var(&res, new_var);
		i++;
	}
	update_shlvl(res);
	return (res);
}