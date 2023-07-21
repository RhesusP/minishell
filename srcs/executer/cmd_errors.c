/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 00:33:42 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/21 09:55:27 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_execve_fail(t_to_free *f, char **cmd, char **env, int nb_p)
{
	ft_putstr_fd(cmd[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	g_status = 127;
	unlink_he_files(f, nb_p);
	free_all(cmd);
	free_all(env);
	free_and_exit(*f, 1, g_status);
}

static void	exit_with_error(t_to_free *f, char **cmd, char *msg, int status)
{
	ft_putstr_fd(cmd[0], STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	g_status = status;
	free_all(cmd);
	free_and_exit(*f, 1, g_status);
}

void	check_dir_err(t_to_free *f, char **cmd, int nb_pipes, struct stat path)
{
	if (S_ISDIR(path.st_mode))
	{
		unlink_he_files(f, nb_pipes);
		exit_with_error(f, cmd, ": Is a directory\n", 126);
	}
	else
	{
		if (access(cmd[0], X_OK) != 0)
		{
			unlink_he_files(f, nb_pipes);
			exit_with_error(f, cmd, ": Permission denied\n", 126);
		}
	}
}

void	check_cmd_err(t_to_free *to_free, char **cmd, int nb_pipes)
{
	struct stat	path;

	if (stat(cmd[0], &path) == 0)
		check_dir_err(to_free, cmd, nb_pipes, path);
	else
	{
		if (ft_strncmp(cmd[0], "./", 2) == 0)
		{
			unlink_he_files(to_free, nb_pipes);
			exit_with_error(to_free, cmd, ": No such file or directory\n", 127);
		}
	}
}
