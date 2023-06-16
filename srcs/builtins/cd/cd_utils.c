/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:51:31 by cbernot           #+#    #+#             */
/*   Updated: 2023/06/16 11:30:45 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env_var	*get_old_pwd(t_env_var *env)
{
	t_env_var	*current;

	if (!env)
		return (0);
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, "OLDPWD") == 0)
			return (current);
		current = current->next;
	}
	return (0);
}

t_env_var	*get_pwd(t_env_var *env)
{
	t_env_var	*current;

	if (!env)
		return (0);
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, "PWD") == 0)
			return (current);
		current = current->next;
	}
	return (0);
}

static int	is_abs_path(char *path)
{
	if (path[0] == '/')
		return (1);
	return (0);
}

static char	*get_valid_pwd(char *pwd, char *input)
{
	char	*path;
	char	*tmp;

	if (is_abs_path(input))
		return (ft_strdup(input));
	if (ft_strlen(ft_strrchr(pwd, '/')) == 1)
		return (ft_strjoin(pwd, input));
	tmp = ft_strjoin(pwd, "/");
	path = ft_strjoin(tmp, input);
	free(tmp);
	return (path);
}

int	count_dir(char *path)
{
	int	i;
	int	reset;
	int	nb;

	reset = 1;
	nb = 0;
	i = 0;
	while (path[i] != '\0')
	{
		if (path[i] != '/' && reset)
		{
			nb++;
			reset = 0;
		}
		else if (path[i] == '/')
			reset = 1;
		i++;
	}
	return (nb);
}
