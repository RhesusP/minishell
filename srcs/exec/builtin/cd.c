/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:23:47 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/03/08 12:33:55 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/exec.h"

void	exec_cd(char *path, t_env_var *env_var)
{
	t_env_var	*pwd;
	char		*tmp;

	pwd = get_env_custom("PWD", env_var);
	if (path[0] = '~')
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
