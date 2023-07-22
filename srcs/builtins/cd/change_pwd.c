/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:26:38 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/22 14:56:27 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief Change the $OLDPWD environment variable.
 * @details It handle the case where the $OLDPWD variable doesn't exist yet.
 * @param env 
 */
static void	change_old_pwd(t_env_var *env)
{
	t_env_var	*old_pwd;
	char		*temp;
	char		*temp1;

	old_pwd = get_old_pwd(env);
	if (!old_pwd)
	{
		temp = ft_getcwd();
		temp1 = ft_strjoin("OLDPWD=", temp);
		free(temp);
		add_back_env_var(&env, create_env_var(temp1));
		free(temp1);
	}
	else
	{
		free_all(old_pwd->values);
		temp = get_pwd(env)->values[0];
		old_pwd->values = malloc(sizeof(char *) * 2);
		old_pwd->values[0] = ft_strdup(temp);
		old_pwd->values[1] = 0;
	}
}

static void	sub_change_pwd(t_env_var *env, char *new_pwd)
{
	t_env_var	*pwd;
	char		*temp;

	pwd = get_pwd(env);
	if (!pwd)
	{
		temp = ft_strjoin("PWD=", new_pwd);
		add_back_env_var(&env, create_env_var(temp));
		free(temp);
	}
	else
	{
		free_all(pwd->values);
		pwd->values = malloc(sizeof(char *) * 2);
		pwd->values[0] = ft_strdup(new_pwd);
		pwd->values[1] = 0;
	}
}

/**
 * @brief Change the current working directory and the old one.
 * 
 * @param env Environment variables list.
 * @param new_pwd New current working directory.
 */
void	change_pwd(t_env_var *env, char *new_pwd)
{
	if (chdir(new_pwd) != 0)
	{
		g_gbl.status = 1;
		perror(new_pwd);
		return ;
	}
	change_old_pwd(env);
	sub_change_pwd(env, new_pwd);
	g_gbl.status = 0;
}
