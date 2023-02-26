/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:57:55 by cbernot           #+#    #+#             */
/*   Updated: 2023/02/26 01:29:35 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

t_env_var	*get_environment(char **env)
{
	int			i;
	t_env_var	*res;
	t_env_var	*new_var;

	res = malloc(sizeof(t_env_var));
	if (!res)
		return (0);
	res = 0;
	i = 0;
	while (env[i])
	{
		new_var = create_env_var(env[i]);	//handle fail
		add_back_end_var(&res, new_var);
		/*
		printf("key: %s\n", temp->key);
		int j = 0;
		while (temp->values[j])
		{
			printf("%s ", temp->values[j]);
			j++;
		}
		printf("\n");
		*/
		i++;
	}
	return (res);
}