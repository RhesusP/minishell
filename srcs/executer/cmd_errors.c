/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 00:33:42 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/19 01:05:51 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_execve_fail(t_to_free *to_free, char **full_cmd, char **str_env)
{
	ft_putstr_fd(full_cmd[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	g_status = 127;
	free_all(full_cmd);
	free_all(str_env);
	free_and_exit(*to_free, 1, g_status);
}

static void	exit_with_error(t_to_free *f, char **cmd, char *msg, int status)
{
	ft_putstr_fd(cmd[0], STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	g_status = status;
	free_all(cmd);
	free_and_exit(*f, 1, g_status);
}

void	check_cmd_err(t_to_free *to_free, char **cmd)
{
	struct stat	path;

	if (stat(cmd[0], &path) == 0)
	{
		if (S_ISDIR(path.st_mode))
			exit_with_error(to_free, cmd, ": Is a directory\n", 126);
		else
		{
			if (access(cmd[0], X_OK) != 0)
				exit_with_error(to_free, cmd, ": Permission denied\n", 126);
		}	
	}
	else
	{
		if (ft_strncmp(cmd[0], "./", 2) == 0)
			exit_with_error(to_free, cmd, ": No such file or directory\n", 127);
	}
}
