/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:23:47 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/04/07 12:39:23 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/exec.h"
/**
 * @brief change PWD variable in t_env_var structure
 * @note 
 * - First case : we got an absolute path to store in structure
 * - Second case : we got a relative path : we need to strjoin to get the absolute path in structure
**/
static void	change_pwd(char *path, t_env_var *pwd)
{
	char		*tmp;
	if (path[0] = '/')
	{	
		free(pwd->values[0]);
		pwd->values[0] = ft_strdup(path);
	}
	else
	{
		tmp = pwd->values[0];
		pwd->values[0] = ft_strjoin(tmp, path);
		free(tmp);
	}
}

/**
 * chdir checks that the path exists
 * then we change PWD and OLDPWD
**/
void	exec_cd(char *path, t_env_var *env_var)
{
	t_env_var	*pwd;
	t_env_var	*oldpwd;

	oldpwd = get_env_custom("OLDPWD", env_var);
	pwd = get_env_custom("PWD", env_var);
	if (chdir(path) == 0)
	{
		change_oldpwd(oldpwd, pwd);
		oldpwd->values = pwd->values;
	}
}

void	ft_cd(t_word **lst, t_env_var *env)
{
	
}